#include <stdio.h>
#include <stdlib.h>

#define POINTS_SIZE 10

typedef struct {
	int x;
	int y;
} s_Point;

typedef struct {
	s_Point pt1;
	s_Point pt2;
} s_Rec;

void enter_point(s_Point *point);
void enter_rec(s_Rec *rec);
int find_highest(s_Point *points);
int point_in_rec(s_Point p, s_Rec rec);

int main() {
	s_Point points[POINTS_SIZE];
	s_Rec rec;
	for(int i = 0; i < POINTS_SIZE; i++) {
		enter_point(points+i);
	}
	enter_rec(&rec);
	int high = find_highest(points);
	printf("Highest: x: %d, y: %d\n", points[high].x, points[high].x);
	printf("%d\n", point_in_rec(points[4], rec));
	
	return 0;
}

void enter_point(s_Point *point) {
	printf("Enter x: ");
	scanf("%d", &(point->x));
	printf("Enter y: ");
	scanf("%d", &(point->y));
}

void enter_rec(s_Rec *rec) {
	printf("Enter point 1:\n");
	enter_point(&(rec->pt1));
	printf("Enter point 2:\n");
	enter_point(&(rec->pt2));
}

int find_highest(s_Point *points) {
	int highest_flag = 1;
	int highest = 0;
	for(int i = 0; i < POINTS_SIZE; i++) {
		if( ( ( points + i ) -> x ) > 0 ) {
			if( ( (points+highest) -> y ) <= ( ( points + i ) -> y ) ) {
				highest = i;
			}
			highest_flag = 0;
		}
	}
	
	if(highest_flag) {
		return -1;
	}
	return highest;	
}

int point_in_rec(s_Point p, s_Rec rec) {
	if( (p.x < rec.pt1.x) || (p.y < rec.pt1.y) ) {
		return 0;
	}
	if( (p.x > rec.pt2.x) || (p.y > rec.pt2.y) ) {
		return 0;
	}
	
	return 1;
}
