import struct
import sys
from pathlib import Path


def read_vlq(data, offset):
    value = 0
    while True:
        byte = data[offset]
        offset += 1
        value = (value << 7) | (byte & 0x7F)
        if byte < 0x80:
            return value, offset


def write_vlq(value):
    encoded = [value & 0x7F]
    value >>= 7
    while value:
        encoded.append(0x80 | (value & 0x7F))
        value >>= 7
    return bytes(reversed(encoded))


def parse_track(data):
    events = []
    offset = 0
    tick = 0
    running_status = None
    order = 0
    while offset < len(data):
        delta, offset = read_vlq(data, offset)
        tick += delta
        status = data[offset]
        if status < 0x80:
            if running_status is None:
                raise ValueError("Running status without a preceding channel event")
            status = running_status
        else:
            offset += 1
            if status < 0xF0:
                running_status = status
        if status == 0xFF:
            meta_type = data[offset]
            offset += 1
            length, offset = read_vlq(data, offset)
            payload = data[offset:offset + length]
            offset += length
            raw = bytes((0xFF, meta_type)) + write_vlq(length) + payload
            kind = ("meta", meta_type)
        elif status in (0xF0, 0xF7):
            length, offset = read_vlq(data, offset)
            payload = data[offset:offset + length]
            offset += length
            raw = bytes((status,)) + write_vlq(length) + payload
            kind = ("sysex", status)
        else:
            event_type = status & 0xF0
            length = 1 if event_type in (0xC0, 0xD0) else 2
            payload = data[offset:offset + length]
            offset += length
            raw = bytes((status,)) + payload
            kind = ("channel", status, payload)
        events.append((tick, order, raw, kind))
        order += 1
    return events


def state_key(kind):
    if kind[0] != "channel":
        return None
    status = kind[1]
    event_type = status & 0xF0
    channel = status & 0x0F
    payload = kind[2]
    if event_type in (0x80, 0x90):
        return None
    if event_type in (0xA0, 0xB0):
        return event_type, channel, payload[0]
    return event_type, channel


def slice_track(events, start_tick, end_tick):
    prior_state = {}
    prior_meta = {}
    prior_sysex = []
    for tick, order, raw, kind in events:
        if tick >= start_tick:
            break
        key = state_key(kind)
        if key is not None:
            prior_state[key] = (tick, order, raw, kind)
        elif kind[0] == "meta" and kind[1] in (0x51, 0x54, 0x58, 0x59):
            prior_meta[kind[1]] = (tick, order, raw, kind)
        elif kind[0] == "sysex":
            prior_sysex.append((tick, order, raw, kind))
    output = []
    state_events = list(prior_meta.values()) + list(prior_state.values()) + prior_sysex
    for _, order, raw, kind in sorted(state_events, key=lambda event: (event[0], event[1])):
        output.append((0, order, raw, kind))
    for tick, order, raw, kind in events:
        if tick < start_tick or tick >= end_tick:
            continue
        if kind[0] == "meta" and kind[1] == 0x2F:
            continue
        output.append((tick - start_tick, order, raw, kind))
    output.sort(key=lambda event: (event[0], event[1]))
    encoded = bytearray()
    previous_tick = 0
    for tick, _, raw, _ in output:
        encoded.extend(write_vlq(tick - previous_tick))
        encoded.extend(raw)
        previous_tick = tick
    encoded.extend(write_vlq(end_tick - start_tick - previous_tick))
    encoded.extend(b"\xFF\x2F\x00")
    return bytes(encoded)


def slice_midi(source, destination, start_beat, end_beat):
    data = Path(source).read_bytes()
    if data[:4] != b"MThd":
        raise ValueError("Not a Standard MIDI file")
    header_length = struct.unpack(">I", data[4:8])[0]
    midi_format, track_count, division = struct.unpack(">HHH", data[8:14])
    if division & 0x8000:
        raise ValueError("SMPTE MIDI divisions are not supported")
    start_tick = start_beat * division
    end_tick = end_beat * division
    if start_tick < 0 or end_tick <= start_tick:
        raise ValueError("Invalid beat range")
    offset = 8 + header_length
    sliced_tracks = []
    for _ in range(track_count):
        if data[offset:offset + 4] != b"MTrk":
            raise ValueError("Missing MIDI track header")
        length = struct.unpack(">I", data[offset + 4:offset + 8])[0]
        track_data = data[offset + 8:offset + 8 + length]
        offset += 8 + length
        sliced_tracks.append(slice_track(parse_track(track_data), start_tick, end_tick))
    output = bytearray()
    output.extend(b"MThd")
    output.extend(struct.pack(">IHHH", 6, midi_format, track_count, division))
    for track in sliced_tracks:
        output.extend(b"MTrk")
        output.extend(struct.pack(">I", len(track)))
        output.extend(track)
    Path(destination).write_bytes(output)


if __name__ == "__main__":
    if len(sys.argv) != 5:
        raise SystemExit("usage: midi_slice.py SOURCE DESTINATION START_BEAT END_BEAT")
    slice_midi(sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]))
