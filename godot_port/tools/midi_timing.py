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


def parse_midi(path):
    data = Path(path).read_bytes()
    track_count, division = struct.unpack(">HH", data[10:14])
    offset = 14
    tempos = [(0, 500000)]
    maximum_tick = 0
    for _ in range(track_count):
        if data[offset:offset + 4] != b"MTrk":
            raise ValueError(path)
        length = struct.unpack(">I", data[offset + 4:offset + 8])[0]
        track = data[offset + 8:offset + 8 + length]
        offset += 8 + length
        cursor = 0
        tick = 0
        running = None
        while cursor < len(track):
            delta, cursor = read_vlq(track, cursor)
            tick += delta
            status = track[cursor]
            if status < 0x80:
                status = running
            else:
                cursor += 1
                if status < 0xF0:
                    running = status
            if status == 0xFF:
                meta_type = track[cursor]
                cursor += 1
                size, cursor = read_vlq(track, cursor)
                payload = track[cursor:cursor + size]
                cursor += size
                if meta_type == 0x51 and size == 3:
                    tempos.append((tick, int.from_bytes(payload, "big")))
            elif status in (0xF0, 0xF7):
                size, cursor = read_vlq(track, cursor)
                cursor += size
            else:
                event_type = status & 0xF0
                cursor += 1 if event_type in (0xC0, 0xD0) else 2
        maximum_tick = max(maximum_tick, tick)
    return division, sorted(tempos, key=lambda item: item[0]), maximum_tick


def seconds_at(tick, division, tempos):
    elapsed = 0.0
    previous_tick = 0
    tempo = 500000
    for tempo_tick, next_tempo in tempos:
        if tempo_tick > tick:
            break
        elapsed += (tempo_tick - previous_tick) * tempo / division / 1000000.0
        previous_tick = tempo_tick
        tempo = next_tempo
    return elapsed + (tick - previous_tick) * tempo / division / 1000000.0


if __name__ == "__main__":
    path = sys.argv[1]
    start_beat = int(sys.argv[2])
    end_beat = int(sys.argv[3])
    division, tempos, maximum_tick = parse_midi(path)
    print(f"{seconds_at(start_beat * division, division, tempos):.6f} {seconds_at(end_beat * division, division, tempos):.6f} {seconds_at(maximum_tick, division, tempos):.6f}")
