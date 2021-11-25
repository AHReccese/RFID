#ifndef RFID_Data
#define RFID_Data

struct point
{
	float x;
	float y;
};

const int Sample_Size = 10;

struct point real_point [Sample_Size] = {
	{10,15},
	{110,25},
	{230,25},
	{230,250},
	{320,313},
	{440,480},
	{650,540},
	{700,540},
	{700,680},
	{750,750}
};

point read_point [Sample_Size] = {
	{11,16.78},
	{114.23,23.456},
	{228.23,26.23},
	{231.23,256.34},
	{324.23,313},
	{435.43,485.343},
	{647.343,545.343},
	{707.432,544.23432},
	{692.232,680.232},
	{754.432,745.322}
};

#endif