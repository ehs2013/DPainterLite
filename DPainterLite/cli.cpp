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
	delay_ms(0);
	do_file();
}

void show_copyright(void) {
	char * name = "DPainter Lite";
	char * copyright = "Copyright (C) 2014-2015 Qi Xiaodong";
	ShellAboutA(GetConsoleWindow(), name, copyright, NULL);
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
	printf("Click on the start point.\n");
	get_coordinate(x1, y1);
	int x2, y2;
	printf("\nClick on the end point place.\n");
	get_coordinate(x2, y2);
	printf("\nPress Enter to select a color for drawing.\n");
	getchar();
	color_t color = get_color();
	printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(color), EGEGET_G(color), EGEGET_B(color));
	int width;
	printf("Input the line width: ");
	scanf("%d", &width);
	PLINE newline = new LINE{ x1, y1, x2, y2, width, color };
	shapes.push_back(SHAPE{ SHAPE_LINE, newline });
	draw(newline);
	delay_ms(0);
	printf("\nA line drawed from (%d, %d) to (%d, %d).\n\n", x1, y1, x2, y2);
}

void draw_circle(void) {
	int x, y;
	printf("\nClick on the center of circle.\n");
	get_coordinate(x, y);
	int r;
	printf("\nInput the radius of the circle.\n");
	scanf("%d", &r);
	getchar();
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	fflush(stdin);
	char draw_border = (char)getchar();
	color_t border = 0;
	color_t fill = 0;
	int borderwidth = 1;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
 		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
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
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;

	}
	PCIRCLE newcircle = new CIRCLE{ x, y, r, drawmode, borderwidth, border, fill };
	shapes.push_back(SHAPE{ SHAPE_CIRCLE, newcircle });
	draw(newcircle);
	delay_ms(0);
	printf("A circle drawed.\n");
}

void draw_ellipse(void) {
	int x, y;
	printf("\nClick on the heart of ellipse.\n");
	get_coordinate(x, y);
	int xr, yr;
	printf("\nInput the X and Y radiuses of the ellipse.\n");
	scanf("%d %d", &xr, &yr);
	getchar();
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	fflush(stdin);
	char draw_border = (char)getchar();
	color_t border = 0;
	color_t fill = 0;
	int borderwidth = 1;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
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
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
		printf("\nPress Enter to select a color for filling.\n");
		getchar();
		fill = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(fill), EGEGET_G(fill), EGEGET_B(fill));
		drawmode = FILL | BORDER;
	}
	PELLIPSE newellipse = new ELLIPSE{ x, y, xr, yr, drawmode, borderwidth, border, fill };
	shapes.push_back(SHAPE{ SHAPE_ELLIPSE, newellipse });
	draw(newellipse);
	delay_ms(0);
	printf("An ellipse drawed.\n");
}

void draw_rectangle(void) {
	int l, t;
	printf("\nClick on the left-top point of the rectangle.\n");
	get_coordinate(l, t);
	int r, b;
	printf("\nClick on the right-buttom point of the rectangle.\n");
	get_coordinate(r, b);
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	fflush(stdin);
	char draw_border = (char)getchar();
	color_t border = 0;
	color_t fill = 0;
	int borderwidth = 1;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
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
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
	}
	PRECTANGLE newrectangle = new RECTANGLE{ l, t, r, b, drawmode, borderwidth, border, fill };
	shapes.push_back(SHAPE{ SHAPE_RECTANGLE, newrectangle });
	draw(newrectangle);
	delay_ms(0);
	printf("A rectangle drawed.\n");
}

void draw_polygon(void) {
	bool stop = false;
	int point_no = 0;
	std::vector<std::pair<int, int>> points;
	while (!stop) {
		int p1, p2;
		printf("Click on the point %d.\n", point_no+1);
		printf("Right click to stop.\n");
		get_coordinate(p1, p2, &stop);
		if ((point_no < 3) && (stop == true)) {
			printf("Only %d points, not enough to build even a triangle!\n", point_no);
			printf("Please input more.\n");
			stop = false;
		} else {
			points.push_back(std::pair<int, int>(p1, p2));
			point_no += 1;
		}
	}
	int drawmode = 0x0;
	printf("\nInput b for drawing a border, f for filling only, a for drawing border and filling: ");
	fflush(stdin);
	char draw_border = getchar();
	getchar();
	color_t border = 0;
	color_t fill = 0;
	int borderwidth = 1;
	if (draw_border == 'b') {
		printf("\nPress Enter to select a color for drawing border.\n");
		getchar();
		border = get_color();
		printf("You selected a color which RGB value is (%d, %d, %d).\n", EGEGET_R(border), EGEGET_G(border), EGEGET_B(border));
		drawmode = BORDER;
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
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
		printf("Input the border width: ");
		scanf("%d", &borderwidth);
	}
	PPOLYGON newpolygon = new POLYGON{ points, drawmode, borderwidth, border, fill };
	shapes.push_back(SHAPE{ SHAPE_POLYGON, newpolygon });
	draw(newpolygon);
	delay_ms(0);
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
