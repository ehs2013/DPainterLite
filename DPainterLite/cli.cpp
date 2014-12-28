#include "cli.h"

std::vector <SHAPE> shapes;
extern rapidjson::Document jsonfile;
extern rapidjson::Value all_shapes;
extern char filename[255];
extern char filetitle[50];

void cli(void) {
	SetConsoleTitleA("Command Window - DPainter Lite");
	while (true) {
		switch (entrance()) {
		case 1:
			new_file();
			break;
		case 2:
			open_file();
			break;
		case 3:
			show_copyright();
			break;
		case 4:
			return;
			exit(0);
		default:
			break;
		}
	}
}

int entrance(void) {
	printf("Welcome to DPainter Lite.\n\n");
	printf("Available Functions: \n");
	printf("1. New\n2. Open\n3. About\n4. Exit\n\n");
	int temp_selection = 0;
	bool select_ok = false;
	int selection = 0;
	printf("Enter the number to do an operation: ");
	scanf("%d", &temp_selection);
	getchar();
	while (!select_ok) {
		if (temp_selection > 0 && temp_selection < 5) {
			select_ok = true;
			selection = temp_selection;
			break;
		} else {
			printf("Input error. Re-enter a number: ");
			scanf("%d", &temp_selection);
			getchar();
		}
	}
	printf("\n");
	return selection;
}

void new_file(void) {
	jsonfile.SetObject();
	initpad();
	do_file();
}

void open_file(void) {
	get_open_filename(filename, "json", filetitle);
	std::vector<char> filechars;
	FILE* file = fopen(filename, "r");
	char tmp = '\0';
	while ((tmp = fgetc(file))!= -1) {
		filechars.push_back(tmp);
	}
	fclose(file);
	char *filecontent = new char[filechars.size() + 1]();
	for (size_t i = 0; i < filechars.size(); i++) {
		filecontent[i] = filechars[i];
	}
	jsonfile.Parse(filecontent);
	char title[70];
	sprintf(title, "%s - Command Window - DPainter Lite", filetitle);
	SetConsoleTitle(title);
	initpad();
	readjson();
	do_file();
}

void show_copyright(void) {
	printf("DPainter Lite\n");
	printf("Copyright (C) 2014-2015 Qi Xiaodong\n");
}

void do_file(void) {
	while (true) {
		switch (file_operation_select()) {
		case 1:
			draw_line();
			break;
		case 2:
			draw_circle();
			break;
		case 3:
			draw_rectangle();
			break;
		case 4:
			draw_ellipse();
			break;
		case 5:
			draw_polygon();
			break;
		case 6:
			save();
			return;
		default:
			break;
		}
	}
}

int file_operation_select(void) {
	printf("Available Functions: \n");
	printf("1. Draw a line\n2. Draw a circle\n3. Draw a rectangle\n4. Draw an ellipse\n5. Draw a polygon\n\n6. Save\n\n");
	int temp_selection = 0;
	bool select_ok = false;
	int selection = 0;
	printf("Enter the number to do an operation: ");
	scanf("%d", &temp_selection);
	while (!select_ok) {
		if (temp_selection > 0 && temp_selection < 7) {
			select_ok = true;
			selection = temp_selection;
			break;
		} else {
			printf("Input error. Re-enter a number: ");
			scanf("%d", &temp_selection);
			getchar();
		}
	}
	printf("\n");
	return selection;
}

void draw_line(void) {
	int x1, y1;
	printf("Input the start point place: ");
	scanf("%d %d", &x1, &y1);
	getchar();
	int x2, y2;
	printf("\nInput the end point place: ");
	scanf("%d %d", &x2, &y2);
	getchar();
	printf("\nPress Enter to select a color for drawing.\n");
	getchar();
	color_t color = get_color();
	printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(color), EGEGET_G(color), EGEGET_B(color));
	PLINE newline = new LINE{ x1, y1, x2, y2, color };
	shapes.push_back(SHAPE{ SHAPE_LINE, newline });
	draw(newline);
	printf("Length: %d", shapes.size());
	delay_fps(1000);
	printf("\nA line drawed from (%d, %d) to (%d, %d).\n\n", x1, y1, x2, y2);
}

void draw_circle(void) {
	int x, y;
	printf("\nInput the heart of circle: ");
	scanf("%d %d", &x, &y);
	getchar();
	int r;
	printf("\nInput the radius of the circle: ");
	scanf("%d", &r);
	getchar();
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	char draw_border = (char)getchar();
	getchar();
	color_t border = 0;
	color_t fill = 0;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
 		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
	} else if (draw_border == 'f') {
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL;
	} else if (draw_border == 'a') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;
	}
	PCIRCLE newcircle = new CIRCLE{ x, y, r, drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_CIRCLE, newcircle });
	draw(newcircle);
	printf("Length: %d\n", shapes.size());
	delay_fps(1000);
	printf("A circle drawed.\n");
}

void draw_ellipse(void) {
	int x, y;
	printf("\nInput the heart of ellipse: ");
	scanf("%d %d", &x, &y);
	getchar();
	int xr, yr;
	printf("\nInput the X and Y radiuses of the ellipse: ");
	scanf("%d %d", &xr, &yr);
	getchar();
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	char draw_border = (char)getchar();
	getchar();
	color_t border = 0;
	color_t fill = 0;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
	} else if (draw_border == 'f') {
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL;
	} else if (draw_border == 'a') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;
	}
	PELLIPSE newellipse = new ELLIPSE{ x, y, xr, yr, drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_ELLIPSE, newellipse });
	draw(newellipse);
	printf("Length: %d\n", shapes.size());
	delay_fps(1000);
	printf("An ellipse drawed.\n");
}

void draw_rectangle(void) {
	int l, t;
	printf("\nInput the left-top point of the rectangle: ");
	scanf("%d %d", &l, &t);
	getchar();
	int r, b;
	printf("\nInput the right-buttom point of the rectangle: ");
	scanf("%d %d", &r, &b);
	getchar();
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	char draw_border = (char)getchar();
	getchar();
	color_t border = 0;
	color_t fill = 0;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
	} else if (draw_border == 'f') {
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL;
	} else if (draw_border == 'a') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;
	}
	PRECTANGLE newrectangle = new RECTANGLE{ l, t, r, b, drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_RECTANGLE, newrectangle });
	draw(newrectangle);
	printf("Length: %d\n", shapes.size());
	delay_fps(1000);
	printf("A rectangle drawed.\n");
}

void draw_polygon(void) {
	bool drawing = true;
	int point_no = 0;
	std::vector<std::pair<int, int>> points;
	while (drawing) {
		int p1, p2;
		char tmps[20];
		printf("Input the point %d: ", point_no+1);
		fflush(stdin);
		fgets(tmps, 20, stdin);
		int input_nums = sscanf(tmps, "%d %d\n", &p1, &p2);
		if ((input_nums == -1) && (point_no < 3)) {
			printf("Only %d points, not enough to build even a triangle!\n", point_no);
			printf("Please input more.\n");
			continue;
		} else if (input_nums == -1) {
			printf("You entered %d points.\n", point_no);
			break;
		} else if (input_nums < 2) {
			printf("Input Error, please re-input.\n");
			continue;
		} else if (input_nums == 2) {
			points.push_back(std::pair<int, int>(p1, p2));
			point_no += 1;
		}
	}
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	char draw_border = (char)getchar();
	getchar();
	color_t border = 0;
	color_t fill = 0;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
	} else if (draw_border == 'f') {
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL;
	} else if (draw_border == 'a') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;
	}
	PPOLYGON newpolygon = new POLYGON{ points, drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_POLYGON, newpolygon });
	draw(newpolygon);
	printf("Length: %d\n", shapes.size());
	delay_fps(1000);
	printf("A polygon drawed.\n");
}

void save(void) {
	for (size_t i = 0; i < shapes.size(); i++) {
		writejson(shapes[i]);
		free(shapes[i].shape);
	}
	shapes.clear();
	cleardevice();
	closegraph();
	finalwrite();
	filename[0] = '\0';
	SetConsoleTitleA("Command Window - DPainter Lite");
}
