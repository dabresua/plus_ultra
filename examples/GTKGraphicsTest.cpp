#include <gtkmm.h>
using namespace std;
using namespace Gtk;

// class definitions

class MathHelper
{
	public: static void seedRandomizer()
	{
		srand(time(NULL));
	}

	public: static double random()
	{
		return ((double)rand()) / RAND_MAX;
	}
};

class Color
{
	public:
		double red;
		double green;
		double blue;

		public: Color() {}

		public: Color(double redIn, double greenIn, double blueIn)
		{
			red = redIn;
			green = greenIn;
			blue = blueIn;
		}

		public: Color* random()
		{
			red = MathHelper::random();
			green = MathHelper::random();
			blue = MathHelper::random();

			return this;
		}
};

class Coords
{
	// variables

	public: double x;
	public: double y;

	// constructor

	public: Coords(int xIn, int yIn)
	{
		this->x = xIn;
		this->y = yIn;
	}

	// methods

	public: Coords* multiply(Coords* other)
	{
		this->x *= other->x;
		this->y *= other->y;
		return this;
	}

	public: Coords* random()
	{
		this->x = MathHelper::random();
		this->y = MathHelper::random();
		return this;
	}
};

class Rectangle
{
	public: Color* color;
	public: Coords* pos;
	public: Coords* size;

	public: Rectangle(Color* colorIn, Coords* posIn, Coords* sizeIn)
	{
		this->color = colorIn;
		this->pos = posIn;
		this->size = sizeIn;
	}

};

class DisplayHelper
{
	// variables

	private: Coords* viewSizeInPixels;
	private: Cairo::RefPtr graphics;

	// constructors

	public: DisplayHelper() {}

	// methods

	public: void initialize(Coords* viewSizeInPixelsIn, DrawingArea* drawingArea)
	{
		viewSizeInPixels = viewSizeInPixelsIn;
		drawingArea->set_size_request
		(
			viewSizeInPixels->x,
			viewSizeInPixels->y
		);
		graphics = drawingArea->get_window()->create_cairo_context();
	}

	public: void drawRectangle(Rectangle* rectangle)
	{
		Color* color = rectangle->color;
		graphics->set_source_rgba
		(
			color->red,
			color->green,
			color->blue,
			1 // alpha
		);

		Coords* pos = rectangle->pos;
		Coords* size = rectangle->size;
		graphics->rectangle(pos->x, pos->y, size->x, size->y);
		graphics->fill();
	}
};

// program
class GTKGraphicsTest : public Window
{
	// controls

	protected: DrawingArea drawingArea;

	// methods

	public: GTKGraphicsTest()
	{
		MathHelper::seedRandomizer();

		set_border_width(10);

		// drawingArea
		drawingArea.signal_expose_event().connect
		(
			sigc::mem_fun
			(
				*this,
				&GTKGraphicsTest::drawingAreaExposed
			)
		);
		add(drawingArea);
		drawingArea.show();
	}

	// events

	protected: bool drawingAreaExposed(GdkEventExpose* event)
	{
		Coords* viewSize = new Coords(100, 100);

		DisplayHelper* displayHelper = new DisplayHelper();
		displayHelper->initialize(viewSize, &drawingArea);

		Rectangle* rectangle = new Rectangle
		(
			(new Color())->random(),
			(new Coords(0, 0))->random()->multiply(viewSize),
			(new Coords(0, 0))->random()->multiply(viewSize)
		);

		displayHelper->drawRectangle
		(
			rectangle
		);
	}
};

// main

int main (int argc, char *argv[])
{
	Main kit(argc, argv);
	GTKGraphicsTest GTKGraphicsTest;
	Main::run(GTKGraphicsTest);
	return 0;
}
