#include "ccv.h"

int main(int argc, char** argv)
{
	ccv_dense_matrix_t* image = 0;
	assert(argc == 3);
	ccv_unserialize(argv[1], &image, CCV_SERIAL_ANY_FILE);
	char* suffix = strrchr(argv[2], '.');
	ccv_dense_matrix_t* representable = 0;
	if (!(image->type & CCV_8U))
	{
		ccv_shift(image, (ccv_matrix_t**)&representable, CCV_8U | CCV_ALL_CHANNEL, 0, 0);
		ccv_dense_matrix_t* t = image;
		image = representable;
		representable = t;
	}
	if (strncmp(suffix, ".png", 4) == 0)
	{
		ccv_serialize(image, argv[2], 0, CCV_SERIAL_PNG_FILE, 0);
	} else if (strncmp(suffix, ".jpg", 4) == 0) {
		ccv_serialize(image, argv[2], 0, CCV_SERIAL_JPEG_FILE, 0);
	}
	ccv_matrix_free(image);
	if (representable != 0)
		ccv_matrix_free(representable);
	ccv_garbage_collect();
	return 0;
}
