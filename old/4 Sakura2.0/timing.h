#ifndef TIMING_H
#define TIMING_H

class Game;

extern int volatile speed_counter;
extern int volatile last_fps;
extern int volatile frame_counter;
extern int volatile cheats;
extern int volatile sound_volume_set;
extern int volatile music_volume_set;
extern DATAFILE * volatile mydatafile;
extern MIDI* stage_music;
extern Game *game;

void increment_speed_counter();
void count_frames();

#endif
