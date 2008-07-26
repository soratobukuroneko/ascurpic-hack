#include <QApplication>
#include <cstdio>
#include "ascurpic.h"
#include "gui.h"

int main(int ac, char **av)
{
	QApplication app(ac, av);
	AscurpiQ     gui;

	/*param_t p;
	int       parse_ret;

	if((parse_ret = parse_opts(&p, ac, av)) < 0)
	{
		std::fprintf(stderr, USAGE, av[0]);
		if (ac == 1)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	disp_info_bmp(p.input_bitmap);
	write_page(&p);
	free_bitmap(p.input_bitmap);*/

	gui.show();
	return app.exec();
}
