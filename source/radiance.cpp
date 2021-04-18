#include "radiance.h"

#include <cstring>

#include <iostream>

using namespace std;

int getByte(istream &in)
{
    int v = in.get();
    if (v == istream::traits_type::eof())
        throw runtime_error { "unexpected end of file" };
    return v;
}

void RadianceMap::load(istream &fin)
{
    constexpr int BUF_SIZE = 512;
    char buf[BUF_SIZE];
    fin.getline(buf, BUF_SIZE);
    if (strncmp(buf, "#?RADIANCE", 10) != 0)
        throw runtime_error { "invalid file ID" };

    bool formatConfirmed = false;
    do
    {
        fin.getline(buf, BUF_SIZE);
        const auto sep = strchr(buf, '=');
        if (sep)
        {
            // TODO: parse all parameters
            if (strncmp(buf, "FORMAT", 6) == 0)
                if (strncmp(sep + 1, "32-bit_rle_rgbe", 15) == 0)
                    formatConfirmed = true;
        }
    }
    while (fin.gcount() > 1);
    if (!formatConfirmed)
        throw runtime_error { "format is not supported" };

    // Dimensions line
    fin >> buf;
    if (strncmp(buf, "-Y", 2) != 0)
        throw runtime_error { "height specifier not found" };

    fin >> m_size.height;
    fin >> buf;
    if (strncmp(buf, "+X", 2) != 0)
        throw runtime_error { "width specifier not found" };

    fin >> m_size.width;
    if (getByte(fin) != '\n')
        throw runtime_error { "cannot find start of data" };

    m_data.reset(new char[m_size.width * 4 * m_size.height]);

    // Scanlines
    for (int h = 0; h < m_size.height; h++)
    {
        int v[] = { getByte(fin), getByte(fin), getByte(fin), getByte(fin) };
        if (v[0] == 2 && v[1] == 2)
        {
            // New RLE
            if (((v[2] << 8) | v[3]) != m_size.width)
                throw runtime_error { "scanline size doesn't match width declared in header" };

            // All R, then all G, then all B...
            for (int cmp = 0; cmp < 4; cmp++)
            {
                for (int p = 0; p < m_size.width;)
                {
                    v[0] = getByte(fin);
                    if (v[0] > 128)
                    {
                        // Run
                        v[0] &= 127;
                        if (v[0] + p > m_size.width)
                            throw  runtime_error { "RLE run is too long" };

                        v[1] = getByte(fin);
                        while (v[0]-- > 0)
                        {
                            m_data[(m_size.width * h + p++) * 4 + cmp] = v[1];
                        }
                    }
                    else if (v[0] > 0)
                    {
                        // Non-run
                        if (v[0] + p > m_size.width)
                            throw  runtime_error { "RLE run is too long" };

                        while (v[0]-- > 0)
                        {
                            m_data[(m_size.width * h + p++) * 4 + cmp] = getByte(fin);
                        }
                    }
                    else
                        throw runtime_error { "incorrect RLE code" };
                }
            }
        }
        else
        {
            // Old RLE / uncompressed
            int pos = 0, rs = 0;
            do
            {
                if (v[0] == 1 && v[1] == 1 && v[2] == 1)
                {
                    if (pos == 0)
                        throw runtime_error { "unexpected repeat indicator in the beginning of the line" };

                    for (int rc = v[3] << rs; rc > 0; rc--)
                    {
                        const int b = (m_size.width * h + pos) * 4,
                                  bp = (m_size.width * h + pos - 1) * 4;
                        for (int i = 0; i < 4; i++)
                            m_data[b + i] = m_data[bp + i];
                        pos++;
                    }
                    rs++;
                }
                else
                {
                    const int b = (m_size.width * h + pos++) * 4;
                    for (int i = 0; i < 4; i++)
                        m_data[b + i] = v[i];
                    rs = 0;
                }
                v[0] = getByte(fin);
                v[1] = getByte(fin);
                v[2] = getByte(fin);
                v[3] = getByte(fin);
            }
            while (pos < m_size.width);
        }
    }
}

Pixel RadianceMap::getPixel(double p, double t) const
{
    return { };
}

void RadianceMap::setPixel(double p, double t, Pixel v)
{

}
