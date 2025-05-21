#ifndef MAIN_HPP
#define MAIN_HPP

#include "linked_list.cpp"

static const int pm_size = 524288;
static const int page_size = 512;
static const int st_size = 1024;

// Integer Array Representing Physical Memory Size
int PM[pm_size];

// 2-D integer array representing disk space for demand paging.
int D[st_size][page_size];

LinkedList free_frames;

#endif