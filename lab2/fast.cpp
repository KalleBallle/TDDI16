#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map> 
#include "hash_map.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

/**
 * Class that stores a summary of an image.
 *
 * This summary is intended to contain a high-level representation of the
 * important parts of an image. I.e. it shall contain what a human eye would
 * find relevant, while ignoring things that the human eye would find
 * irrelevant.
 *
 * To approximate human perception, we store a series of booleans that indicate
 * if the brightness of the image has increased or not. We do this for all
 * horizontal lines and vertical lines in a downsampled version of the image.
 *
 * See the lab instructions for more details.
 *
 * Note: You will need to use this data structure as the key in a hash table. As
 * such, you will need to implement equality checks and a hash function for this
 * data structure.
 */
class Image_Summary {
public:
    // Horizontal increases in brightness.
    vector<bool> horizontal;

    // Vertical increases in brightness.
    vector<bool> vertical;
};

// Compute an Image_Summary from an image. This is described in detail in the
// lab instructions.
Image_Summary compute_summary(const Image &image) {
    const size_t summary_size = 8;
    Image_Summary result;
    
    // TODO: Finish the implementation.
    // auto new_image = image.shrink(summary_size + 1, summary_size + 1);
    
    for(size_t x{0}; x < summary_size + 1; ++x){
        for(size_t y{0}; y < summary_size + 1; ++y){
            if(x != summary_size){
                if(image.pixel(x,y).brightness() < image.pixel(x + 1, y).brightness()){
                    result.horizontal.push_back(true);
                }else{
                    result.horizontal.push_back(false); 
                }
            }
            if(y != summary_size){
                if(image.pixel(x,y).brightness() < image.pixel(x, y + 1).brightness()){
                    result.vertical.push_back(true);
                }else{
                    result.vertical.push_back(false);
                }
            }
        }
    }

    // The lines below are here to avoid warnings. They can be removed.
    //(void)image;
    //(void)summary_size;
    return result;
} 

 bool operator ==(const Image_Summary &left,const Image_Summary &right) 
 {
    return left.horizontal == right.horizontal && left.vertical == right.vertical;
 } 


// Definiera en typ som specialiserar std::hash för vår typ:
template <>
class std::hash<Image_Summary> {
public:
    // Typen ska kunna användas som ett funktionsobjekt.
    // Vi behöver därför överlagra funktionsanropsoperatorn (operator ()).
    size_t operator ()(const Image_Summary &to_hash) const { 
    
        size_t h = 0, v = 0;
        for (size_t i{0}; i < to_hash.horizontal.size(); ++i)
            h ^= (h << 1) | to_hash.horizontal[i];
        for (size_t i{0}; i < to_hash.vertical.size(); ++i)
            v ^= (v << 1) | to_hash.vertical[i];
    
        // Beräkna hash här...
    return h ^ v;
    }
};

std::hash<Image_Summary> hash_function; 

int main(int argc, const char *argv[]) {
    WindowPtr window = Window::create(argc, argv);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1]);
    //cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0) {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    } 

    auto begin = std::chrono::high_resolution_clock::now();

    /**
     * TODO:
     * - For each file:
     *   - Load the file
     *   - Compute its summary 

     */
    window->show_single("Loading images...", load_image(files[0]), false);

     const size_t image_size = 9;
     vector<Image> images;
    for (const auto &file : files) 
    {
        images.push_back(load_image(file).shrink(image_size, image_size));
    }
    auto load_time = std::chrono::high_resolution_clock::now();
    cout << "Loading images took: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(load_time - begin).count()
         << " milliseconds." << endl;


     Hash_Map< Image_Summary, vector<std::string>> coolMap;
    vector<std::pair<size_t,std::string>> matches;
     for (size_t i{};i<=images.size(); ++i) 
     {


        if (files[i].empty())
            continue;

        //images.push_back(load_image(file));   

        coolMap[compute_summary(images[i])].push_back(files[i]); 

        //window->show_single("Comparing images...", load_image(files[1]), false);

/*
        //size_t hash_key = hash_function(compute_summary(image));
           if(coolMap.insert(std::make_pair(compute_summary(image), file)) == false ) 
           { 
            cout << "MATCH: " << file << endl; 
            std::string dudeMan = coolMap[hash_key];
            matches.push_back(make_pair(hash_key,file));
            window->show_pair(dudeMan, load_image(dudeMan), file, image, true);
        }     
            */
    }
    
    
    /**
    * TODO:
    * - Display sets of files with equal summaries
    */ 

    for(auto item : coolMap) 
    {
        if(item.second.size() > 1) 
        {
             window->report_match(item.second);
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Total time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds." << endl;
    
    return 0;
}
