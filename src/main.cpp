#include <nanovdb/util/OpenToNanoVDB.h> // converter from OpenVDB to NanoVDB (includes NanoVDB.h and GridManager.h)
#include <nanovdb/util/IO.h>
#include <openvdb/openvdb.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "This program expects the following format: ./opentonano path_to_open.vdb path_to_output_nano.nvdb" << std::endl;
        return 1;
    }

    std::string input = std::string(argv[1]);
    std::string output = std::string(argv[2]);

    try
    {
        std::cout << "converting " << input << " to nanovdb format and writing to " << output << std::endl;

        openvdb::initialize();
        // Create a VDB file object.
        openvdb::io::File file(input);
        // Open the file.  This reads the file header, but not any grids.
        file.open();
        // Loop over all grids in the file and retrieve a shared pointer
        // to the one named "density".  (This can also be done
        // more simply by calling file.readGrid("density").)
        openvdb::GridBase::Ptr baseGrid;
        for (openvdb::io::File::NameIterator nameIter = file.beginName();
             nameIter != file.endName(); ++nameIter)
        {
            // Read in only the grid we are interested in.
            if (nameIter.gridName() == "density")
            {
                baseGrid = file.readGrid(nameIter.gridName());
            }
            else
            {
                std::cout << "skipping grid " << nameIter.gridName() << std::endl;
            }
        }
        file.close();
        // From the example above, "density" is known to be a FloatGrid,
        // so cast the generic grid pointer to a FloatGrid pointer.
        openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

        // Convert the OpenVDB grid into a NanoVDB grid handle.
        auto handle = nanovdb::openToNanoVDB(*grid);
        // Define a (raw) pointer to the NanoVDB grid on the host. Note we match the value type of the srcGrid!
        auto *dstGrid = handle.grid<float>();
        if (!dstGrid)
            throw std::runtime_error("GridHandle does not contain a grid with value type float");

        nanovdb::io::writeGrid("data/" + output, handle); // Write the NanoVDB grid to file and throw if writing fails
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: \"" << e.what() << "\"" << std::endl;
        return 1;
    }

    std::cout << "finished converting vdb into nvdb!" << std::endl;

    return 0;
}