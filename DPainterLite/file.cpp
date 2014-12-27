#include "file.h"

rapidjson::Document jsonfile;
rapidjson::Value all_shapes(rapidjson::kArrayType);
char filename[255] = "";
char filetitle[50] = "";
extern std::vector<SHAPE> shapes;

void writejson(LINE _line) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	rapidjson::Value jsonline(rapidjson::kObjectType);
	jsonline.AddMember("type", "line", fileallocator);
	rapidjson::Value info(rapidjson::kObjectType);
	info.AddMember("x1", _line.x1, fileallocator);
	info.AddMember("x2", _line.x2, fileallocator);
	info.AddMember("y1", _line.y1, fileallocator);
	info.AddMember("y2", _line.y2, fileallocator);
	rapidjson::Value color(rapidjson::kObjectType);
	color.AddMember("R", EGEGET_R(_line.color), fileallocator);
	color.AddMember("G", EGEGET_G(_line.color), fileallocator);
	color.AddMember("B", EGEGET_B(_line.color), fileallocator);
	info.AddMember("color", color, fileallocator);
	jsonline.AddMember("detail", info, fileallocator);
	all_shapes.PushBack(jsonline, fileallocator);
}

void writejson(CIRCLE _circle) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	rapidjson::Value jsoncircle(rapidjson::kObjectType);
	jsoncircle.AddMember("type", "circle", fileallocator);
	rapidjson::Value info(rapidjson::kObjectType);
	info.AddMember("x", _circle.x, fileallocator);
	info.AddMember("y", _circle.y, fileallocator);
	info.AddMember("radius", _circle.radius, fileallocator);
	rapidjson::Value border(rapidjson::kObjectType);
	bool border_enabled = (_circle.drawmode & BORDER) ? true : false;
	border.AddMember("enabled", border_enabled, fileallocator);
	rapidjson::Value border_color(rapidjson::kObjectType);
	border_color.AddMember("R", EGEGET_R(_circle.bordercolor), fileallocator);
	border_color.AddMember("G", EGEGET_G(_circle.bordercolor), fileallocator);
	border_color.AddMember("B", EGEGET_B(_circle.bordercolor), fileallocator);
	if (border_enabled) {
		border.AddMember("color", border_color, fileallocator);
	}
	rapidjson::Value fill(rapidjson::kObjectType);
	bool fill_enabled = (_circle.drawmode & FILL) ? true : false;
	fill.AddMember("enabled", fill_enabled, fileallocator);
	rapidjson::Value fill_color(rapidjson::kObjectType);
	fill_color.AddMember("R", EGEGET_R(_circle.fillcolor), fileallocator);
	fill_color.AddMember("G", EGEGET_G(_circle.fillcolor), fileallocator);
	fill_color.AddMember("B", EGEGET_B(_circle.fillcolor), fileallocator);
	if (fill_enabled) {
		fill.AddMember("color", fill_color, fileallocator);
	}
	info.AddMember("border", border, fileallocator);
	info.AddMember("fill", fill, fileallocator);
	jsoncircle.AddMember("detail", info, fileallocator);
	all_shapes.PushBack(jsoncircle, fileallocator);
}

void writejson(RECTANGLE _rectangle) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	rapidjson::Value jsonrectangle(rapidjson::kObjectType);
	jsonrectangle.AddMember("type", "triangle", fileallocator);
	rapidjson::Value info(rapidjson::kObjectType);
	info.AddMember("left", _rectangle.left, fileallocator);
	info.AddMember("top", _rectangle.top, fileallocator);
	info.AddMember("right", _rectangle.right, fileallocator);
	info.AddMember("bottom", _rectangle.bottom, fileallocator);
	rapidjson::Value border(rapidjson::kObjectType);
	bool border_enabled = (_rectangle.drawmode & BORDER) ? true : false;
	border.AddMember("enabled", border_enabled, fileallocator);
	rapidjson::Value border_color(rapidjson::kObjectType);
	border_color.AddMember("R", EGEGET_R(_rectangle.bordercolor), fileallocator);
	border_color.AddMember("G", EGEGET_G(_rectangle.bordercolor), fileallocator);
	border_color.AddMember("B", EGEGET_B(_rectangle.bordercolor), fileallocator);
	if (border_enabled) {
		border.AddMember("color", border_color, fileallocator);
	}
	rapidjson::Value fill(rapidjson::kObjectType);
	bool fill_enabled = (_rectangle.drawmode & FILL) ? true : false;
	fill.AddMember("enabled", fill_enabled, fileallocator);
	rapidjson::Value fill_color(rapidjson::kObjectType);
	fill_color.AddMember("R", EGEGET_R(_rectangle.fillcolor), fileallocator);
	fill_color.AddMember("G", EGEGET_G(_rectangle.fillcolor), fileallocator);
	fill_color.AddMember("B", EGEGET_B(_rectangle.fillcolor), fileallocator);
	if (fill_enabled) {
		fill.AddMember("color", fill_color, fileallocator);
	}
	info.AddMember("border", border, fileallocator);
	info.AddMember("fill", fill, fileallocator);
	jsonrectangle.AddMember("detail", info, fileallocator);
	all_shapes.PushBack(jsonrectangle, fileallocator);
}

void writejson(ELLIPSE _ellipse) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	rapidjson::Value jsonellipse (rapidjson::kObjectType);
	jsonellipse.AddMember("type", "ellipse", fileallocator);
	rapidjson::Value info(rapidjson::kObjectType);
	info.AddMember("x", _ellipse.x, fileallocator);
	info.AddMember("y", _ellipse.y, fileallocator);
	info.AddMember("xradius", _ellipse.xradius, fileallocator);
	info.AddMember("yradius", _ellipse.yradius, fileallocator);
	rapidjson::Value border(rapidjson::kObjectType);
	bool border_enabled = (_ellipse.drawmode & BORDER) ? true : false;
	border.AddMember("enabled", border_enabled, fileallocator);
	rapidjson::Value border_color(rapidjson::kObjectType);
	border_color.AddMember("R", EGEGET_R(_ellipse.bordercolor), fileallocator);
	border_color.AddMember("G", EGEGET_G(_ellipse.bordercolor), fileallocator);
	border_color.AddMember("B", EGEGET_B(_ellipse.bordercolor), fileallocator);
	if (border_enabled) {
		border.AddMember("color", border_color, fileallocator);
	}
	rapidjson::Value fill(rapidjson::kObjectType);
	bool fill_enabled = (_ellipse.drawmode & FILL) ? true : false;
	fill.AddMember("enabled", fill_enabled, fileallocator);
	rapidjson::Value fill_color(rapidjson::kObjectType);
	fill_color.AddMember("R", EGEGET_R(_ellipse.fillcolor), fileallocator);
	fill_color.AddMember("G", EGEGET_G(_ellipse.fillcolor), fileallocator);
	fill_color.AddMember("B", EGEGET_B(_ellipse.fillcolor), fileallocator);
	if (fill_enabled) {
		fill.AddMember("color", fill_color, fileallocator);
	}
	info.AddMember("border", border, fileallocator);
	info.AddMember("fill", fill, fileallocator);
	jsonellipse.AddMember("detail", info, fileallocator);
	all_shapes.PushBack(jsonellipse, fileallocator);
}

void writejson(POLYGON _polygon) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	rapidjson::Value jsonpolygon (rapidjson::kObjectType);
	jsonpolygon.AddMember("type", "polygon", fileallocator);
	rapidjson::Value info(rapidjson::kObjectType);
	rapidjson::Value points(rapidjson::kArrayType);
	std::vector<rapidjson::Value> point_ints(_polygon.points.size());
	for (size_t i = 0; i < _polygon.points.size(); i++) {
		point_ints[i].SetObject();
		point_ints[i].AddMember("x", _polygon.points[i].first, fileallocator);
		point_ints[i].AddMember("y", _polygon.points[i].second, fileallocator);
		points.PushBack(point_ints[i], fileallocator);
	}
	info.AddMember("points", points, fileallocator);
	rapidjson::Value border(rapidjson::kObjectType);
	bool border_enabled = (_polygon.drawmode & BORDER) ? true : false;
	border.AddMember("enabled", border_enabled, fileallocator);
	rapidjson::Value border_color(rapidjson::kObjectType);
	border_color.AddMember("R", EGEGET_R(_polygon.bordercolor), fileallocator);
	border_color.AddMember("G", EGEGET_G(_polygon.bordercolor), fileallocator);
	border_color.AddMember("B", EGEGET_B(_polygon.bordercolor), fileallocator);
	if (border_enabled) {
		border.AddMember("color", border_color, fileallocator);
	}
	rapidjson::Value fill(rapidjson::kObjectType);
	bool fill_enabled = (_polygon.drawmode & FILL) ? true : false;
	fill.AddMember("enabled", fill_enabled, fileallocator);
	rapidjson::Value fill_color(rapidjson::kObjectType);
	fill_color.AddMember("R", EGEGET_R(_polygon.fillcolor), fileallocator);
	fill_color.AddMember("G", EGEGET_G(_polygon.fillcolor), fileallocator);
	fill_color.AddMember("B", EGEGET_B(_polygon.fillcolor), fileallocator);
	if (fill_enabled) {
		fill.AddMember("color", fill_color, fileallocator);
	}
	info.AddMember("border", border, fileallocator);
	info.AddMember("fill", fill, fileallocator);
	jsonpolygon.AddMember("detail", info, fileallocator);
	all_shapes.PushBack(jsonpolygon, fileallocator);
}

void writejson(PCIRCLE _pcircle) {
	writejson(*_pcircle);
}

void writejson(PRECTANGLE _prectangle) {
	writejson(*_prectangle);
}

void writejson(PELLIPSE _pellipse) {
	writejson(*_pellipse);
}

void writejson(PLINE _pline) {
	writejson(*_pline);
}

void writejson(PPOLYGON _ppolygon) {
	writejson(*_ppolygon);
}

void writejson(SHAPE _shape) {
	switch (_shape.type) {
	case SHAPE_CIRCLE:
		writejson((PCIRCLE)_shape.shape);
		break;
	case SHAPE_ELLIPSE:
		writejson((PELLIPSE)_shape.shape);
		break;
	case SHAPE_RECTANGLE:
		writejson((PRECTANGLE)_shape.shape);
		break;
	case SHAPE_LINE:
		writejson((PLINE)_shape.shape);
		break;
	case SHAPE_POLYGON:
		writejson((PPOLYGON)_shape.shape);
		break;
	default:
		break;
	}
	delay_fps(1000);
}

void writejson(PSHAPE _pshape) {
	writejson(*_pshape);
}

void finalwrite(void) {
	rapidjson::Document::AllocatorType& fileallocator = jsonfile.GetAllocator();
	jsonfile.AddMember("creator", "DPainter Lite", fileallocator);
	jsonfile.AddMember("version", 1.0, fileallocator);
	jsonfile.AddMember("shapes", all_shapes, fileallocator);
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	jsonfile.Accept(writer);
	if (filename[0] == '\0') {
		char savefilename[255];
		get_save_filename(savefilename, "json");
		FILE * json = fopen(savefilename, "wb");
		fprintf(json, buffer.GetString());
		fprintf(json, "\n");
		fclose(json);
		printf("File saved to %s.\n", savefilename);
	} else {
		FILE * json = fopen(filename, "wb");
		fprintf(json, buffer.GetString());
		fprintf(json, "\n");
		fclose(json);
		printf("File saved to %s.\n", filename);
	}

	jsonfile.RemoveMember("creator");
	jsonfile.RemoveMember("version");
	jsonfile.RemoveMember("shapes");
	all_shapes.SetArray(); // seemed it resetted.
}

void readjson(void) {
	rapidjson::Value tmp_shapes(rapidjson::kArrayType);
	tmp_shapes = jsonfile["shapes"];
	for (rapidjson::SizeType i = 0; i < tmp_shapes.Size(); i++) {
		if (strcmp(tmp_shapes[i]["type"].GetString(), "circle") == 0) {
			readcircle(tmp_shapes[i]["detail"]);
		} else if (strcmp(tmp_shapes[i]["type"].GetString(), "line") == 0) {
			readline(tmp_shapes[i]["detail"]);
		} else if (strcmp(tmp_shapes[i]["type"].GetString(), "ellipse") == 0) {
			readellipse(tmp_shapes[i]["detail"]);
		} else if (strcmp(tmp_shapes[i]["type"].GetString(), "rectangle") == 0) {
			readrectangle(tmp_shapes[i]["detail"]);
		} else if (strcmp(tmp_shapes[i]["type"].GetString(), "polygon") == 0) {
			readpolygon(tmp_shapes[i]["detail"]);
		}
	}
	jsonfile.RemoveMember("creator");
	jsonfile.RemoveMember("author");
	jsonfile.RemoveMember("version");
	jsonfile.RemoveMember("shapes");
}

void readcircle(rapidjson::Value& _circle) {
	int drawmode = 0x0;
	color_t border = 0;
	color_t fill = 0;
	if (_circle["border"]["enabled"].GetBool()) {
		drawmode |= BORDER;
		border = EGERGB(_circle["border"]["color"]["R"].GetInt(), _circle["border"]["color"]["G"].GetInt(), _circle["border"]["color"]["B"].GetInt());
	}
	if (_circle["fill"]["enabled"].GetBool()) {
		drawmode |= FILL;
		fill = EGERGB(_circle["fill"]["color"]["R"].GetInt(), _circle["fill"]["color"]["G"].GetInt(), _circle["fill"]["color"]["B"].GetInt());
	}
	PCIRCLE newcircle = new CIRCLE{ _circle["x"].GetInt(), _circle["y"].GetInt(), _circle["radius"].GetInt(), drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_CIRCLE, newcircle });
	draw(shapes.back());
}

void readline(rapidjson::Value& _line) {
	PLINE newline = new LINE{ _line["x1"].GetInt(), _line["y1"].GetInt(), _line["x2"].GetInt(), _line["y2"].GetInt(), EGERGB(_line["color"]["R"].GetInt(), _line["color"]["G"].GetInt(), _line["color"]["B"].GetInt()) };
	shapes.push_back(SHAPE{ SHAPE_LINE, newline });
	draw(shapes.back());
}

void readrectangle(rapidjson::Value& _rectangle) {
	int drawmode = 0x0;
	color_t border = 0;
	color_t fill = 0;
	if (_rectangle["border"]["enabled"].GetBool()) {
		drawmode |= BORDER;
		border = EGERGB(_rectangle["border"]["color"]["R"].GetInt(), _rectangle["border"]["color"]["G"].GetInt(), _rectangle["border"]["color"]["B"].GetInt());
	}
	if (_rectangle["fill"]["enabled"].GetBool()) {
		drawmode |= FILL;
		fill = EGERGB(_rectangle["fill"]["color"]["R"].GetInt(), _rectangle["fill"]["color"]["G"].GetInt(), _rectangle["fill"]["color"]["B"].GetInt());
	}
	PRECTANGLE newrectangle = new RECTANGLE{ _rectangle["left"].GetInt(), _rectangle["top"].GetInt(), _rectangle["right"].GetInt(), _rectangle["bottom"].GetInt(), drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_RECTANGLE, newrectangle });
	draw(shapes.back());
}

void readellipse(rapidjson::Value& _ellipse) {
	int drawmode = 0x0;
	color_t border = 0;
	color_t fill = 0;
	if (_ellipse["border"]["enabled"].GetBool()) {
		drawmode |= BORDER;
		border = EGERGB(_ellipse["border"]["color"]["R"].GetInt(), _ellipse["border"]["color"]["G"].GetInt(), _ellipse["border"]["color"]["B"].GetInt());
	}
	if (_ellipse["fill"]["enabled"].GetBool()) {
		drawmode |= FILL;
		fill = EGERGB(_ellipse["fill"]["color"]["R"].GetInt(), _ellipse["fill"]["color"]["G"].GetInt(), _ellipse["fill"]["color"]["B"].GetInt());
	}
	PELLIPSE newellipse = new ELLIPSE{ _ellipse["x"].GetInt(), _ellipse["y"].GetInt(), _ellipse["xradius"].GetInt(), _ellipse["yradius"].GetInt(), drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_ELLIPSE, newellipse });
	draw(shapes.back());
}

void readpolygon(rapidjson::Value& _polygon) {
	int drawmode = 0x0;
	color_t border = 0;
	color_t fill = 0;
	if (_polygon["border"]["enabled"].GetBool()) {
		drawmode |= BORDER;
		border = EGERGB(_polygon["border"]["color"]["R"].GetInt(), _polygon["border"]["color"]["G"].GetInt(), _polygon["border"]["color"]["B"].GetInt());
	}
	if (_polygon["fill"]["enabled"].GetBool()) {
		drawmode |= FILL;
		fill = EGERGB(_polygon["fill"]["color"]["R"].GetInt(), _polygon["fill"]["color"]["G"].GetInt(), _polygon["fill"]["color"]["B"].GetInt());
	}
	std::vector<std::pair<int, int>> points;
	for (rapidjson::SizeType i = 0; i < _polygon["points"].Size(); i++) {
		points.push_back(std::pair<int, int>(_polygon["points"][i]["x"].GetInt(), _polygon["points"][i]["y"].GetInt()));
	}
	PPOLYGON newpolygon = new POLYGON{ points, drawmode, border, fill };
	shapes.push_back(SHAPE{ SHAPE_POLYGON, newpolygon });
	draw(shapes.back());
}