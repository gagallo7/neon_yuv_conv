#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void from_yv12_to_nv21(const uint8_t* yv12,
                       int stride,
                       int scanline,
                       uint8_t* nv21_vu_plane
                      )
{
    const int y_plane_size = stride * scanline;

    const int subsampled_stride = stride / 2;
    const int subsampled_scanline = scanline / 2;

    const uint8_t* v_plane = yv12 + y_plane_size;
    const uint8_t* u_plane = v_plane + subsampled_scanline * subsampled_stride;

    for (int element = 0; element < subsampled_stride * subsampled_scanline; ++element) {
        *nv21_vu_plane++ = v_plane[element];
        *nv21_vu_plane++ = u_plane[element];
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Input file, stride and/or scanline is missing." << endl;
        return -1;
    }

    const string filename(argv[1]);
    const int width = stoi(argv[2]);
    const int height = stoi(argv[3]);

    uint8_t* yv12_image_ptr = static_cast<uint8_t*>(malloc((width * height * 3) / 2));

    unique_ptr<uint8_t> yv12_image(yv12_image_ptr);

    ifstream in_file(filename, in_file.in);

    if (in_file.is_open()) {
        in_file.seekg(0, std::ios::end);
        const int size = in_file.tellg();
        in_file.seekg(0, std::ios::beg);
        in_file.read(reinterpret_cast<char*>(yv12_image.get()), size);
        in_file.close();
    }
    else {
        cout << "Error: Cannot read file " << argv[1] << endl;
        return -1;
    }

    uint8_t* nv21_image = nullptr;
    nv21_image = static_cast<uint8_t*>(malloc(width * height / 2));

    from_yv12_to_nv21(yv12_image.get(),
                      width,
                      height,
                      nv21_image
                     );

    const string out_filename(filename + ".nv21");
    fstream out_file(out_filename, ios::binary | ios::out);

    // Goto the beginning of the file
    if (out_file.is_open()) {
        out_file.write(reinterpret_cast<char*>(yv12_image_ptr), width * height);
        out_file.write(reinterpret_cast<char*>(nv21_image), width * height / 2);
        out_file.close();
    }
    else {
        cout << "Error: Cannot write file " << argv[1] << ".nv21" << endl;
        return -1;
    }

    if (nv21_image != nullptr) {
        free(nv21_image);
    }

    return 0;
}
