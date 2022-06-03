// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015-2017 Intel Corporation. All Rights Reserved.

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include "example.hpp"          // Include short list of convenience functions for rendering

#include <map>
#include <vector>

int main(int argc, char *argv[])
{
    try
    {
        // Create a simple OpenGL window for rendering:
        window app(1280, 960, "CPP Multi-Camera Example");

        rs2::context ctx;
        std::map<std::string, rs2::colorizer> colorizers;
        std::vector<rs2::pipeline> pipelines;

        std::vector<std::string> serials;
        for (auto &&dev : ctx.query_devices())
            serials.push_back(dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));

        for (auto &&serial : serials)
        {
            rs2::pipeline pipe(ctx);
            rs2::config cfg;
            cfg.enable_device(serial);
            pipe.start(cfg);
            pipelines.emplace_back(pipe);
            colorizers[serial] = rs2::colorizer();
        }

        std::map<int, rs2::frame> render_frames;

        while (app)
        {
            std::vector<rs2::frame> new_frames;
            for (auto &&pipe : pipelines)
            {
                rs2::frameset fs;
                if (pipe.poll_for_frames(&fs)) for (const rs2::frame &f : fs) new_frames.emplace_back(f);
            }

            for (const auto &frame : new_frames)
            {
                auto serial = rs2::sensor_from_frame(frame)->get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
                render_frames[frame.get_profile().unique_id()] = colorizers[serial].process(frame);
            }

            app.show(render_frames);
        }

        return EXIT_SUCCESS;
    }
    catch (const rs2::error &e)
    {
        std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}