#include "draw.h"

void draw(CIRCLE _circle) {
	if (_circle.drawmode & BORDER) {
		setcolor(_circle.bordercolor);
		circle(_circle.x, _circle.y, _circle.radius);
	}
	if (_circle.drawmode & FILL) {
		setfillcolor(_circle.fillcolor);
		fillellipse(_circle.x, _circle.y, _circle.radius, _circle.radius);
	}
}

void draw(RECTANGLE _rectangle) {
	if (_rectangle.drawmode & BORDER) {
		setcolor(_rectangle.bordercolor);
		rectangle(_rectangle.left, _rectangle.top, _rectangle.right, _rectangle.bottom);
	}
	if (_rectangle.drawmode & FILL) {
		setfillcolor(_rectangle.fillcolor);
		bar(_rectangle.left, _rectangle.top, _rectangle.right, _rectangle.bottom);
	}
}

void draw(ELLIPSE _ellipse) {
	if (_ellipse.drawmode & BORDER) {
		setcolor(_ellipse.bordercolor);
		ellipse(_ellipse.x, _ellipse.y, 0, 0, _ellipse.xradius, _ellipse.yradius);
	}
	if (_ellipse.drawmode & FILL) {
		setfillcolor(_ellipse.fillcolor);
		fillellipse(_ellipse.x, _ellipse.y, _ellipse.xradius, _ellipse.yradius);
	}
}

void draw(LINE _line) {
	setcolor(_line.color);
	setfillcolor(_line.color);
	line(_line.x1, _line.y1, _line.x2, _line.y2);
}

void draw(POLYGON _polygon) {
	int numpoints = _polygon.points.size() + 1;
	int *polypoints = new int[2 + 2 * _polygon.points.size()];
	for (size_t i = 0; i < _polygon.points.size(); i++) {
		polypoints[i * 2] = _polygon.points[i].first;
		polypoints[i * 2 + 1] = _polygon.points[i].second;
	}
	polypoints[_polygon.points.size() * 2] = _polygon.points[0].first;
	polypoints[_polygon.points.size() * 2 + 1] = _polygon.points[0].second;
	if (_polygon.drawmode & BORDER) {
		setcolor(_polygon.bordercolor);
		drawpoly(numpoints, polypoints);
	}
	if (_polygon.drawmode & FILL) {
		setfillcolor(_polygon.fillcolor);
		fillpoly(numpoints, polypoints);
	}
	delete[] polypoints;
}

void draw(PCIRCLE _pcircle) {
	draw(*_pcircle);
}

void draw(PRECTANGLE _prectangle) {
	draw(*_prectangle);
}

void draw(PELLIPSE _pellipse) {
	draw(*_pellipse);
}

void draw(PLINE _pline) {
	draw(*_pline);
}

void draw(PPOLYGON _ppolygon) {
	draw(*_ppolygon);
}

void draw(SHAPE _shape) {
	switch (_shape.type) {
	case SHAPE_CIRCLE:
		draw((PCIRCLE)_shape.shape);
		break;
	case SHAPE_ELLIPSE:
		draw((PELLIPSE)_shape.shape);
		break;
	case SHAPE_RECTANGLE:
		draw((PRECTANGLE)_shape.shape);
		break;
	case SHAPE_LINE:
		draw((PLINE)_shape.shape);
		break;
	case SHAPE_POLYGON:
		draw((PPOLYGON)_shape.shape);
		break;
	default:
		break;
	}
}

void draw(PSHAPE _pshape) {
	draw(*_pshape);
}