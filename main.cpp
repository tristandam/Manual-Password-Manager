#include <iostream>
#include "HashMap.hpp"


int main() {
//    HashMap h1;
//    h1.add("Sebastian", "sseibertvonfock@gmail.com");
//    h1.add("Tristan", "tddam@uci.edu");
//    h1.add("Martin", "mintmartini100@gmail.com");
//    h1.add("Frank","frankcao96@yahoo.com");
//    h1.add("a","frankcao96@yahoo.com");
//    h1.add("b","frankcao96@yahoo.com");
//    h1.add("ac","frankcao96@yahoo.com");
//    HashMap h2 = h1;
   
 
//    std::cout << h1.size() << std::endl;
//    std::cout << h1.loadFactor() << std::endl;
//    h1.add("ad","frankcao96@yahoo.com");
//    h1.add("ads","frankcao96@yahoo.com");
//    h1.add("asad","frankcao96@yahoo.com");
//    h1.add("adsaasa","frankcao96@yahoo.com");
//    std::cout << h1.size() << std::endl;
//    std::cout << h1.loadFactor() << std::endl;
//    h1.clear();
//    std::cout << h1.size() << std::endl;
//    std::cout << h1.loadFactor() << std::endl;
//    h1.add("ae","frankcao96@yahoo.com");
//    h1.add("af","frankcao96@yahoo.com");
//    h1.add("aa","frankcao96@yahoo.com");
//    h1.add("Tristan","yopperpo@gmail.com");
//    h1.add("Tristan","yopperspo@gmail.com");
//    h1.add("Tristan","yopdwaperpo@gmail.com");
//    h1.remove("Tristan");
//    h1.remove("Sebastian");
//    h1.remove("b");
//    h1.remove("thingnotthere");
//    std::cout << h1.value("ae") << std::endl;
//
//    std::cout << h1.contains("Sebastian") << std::endl;
//    h1.remove("Sebastian");
//    std::cout << h1.contains("Sebastian") << std::endl;
//
//    std::cout << h1.size() << std::endl;
//    std::cout << h1.bucketCount() << std::endl;
//    std::cout << h1.loadFactor() << std::endl;
//
    std::cout << "HI" << std::endl;
    std::string command;
    std::string key;
    std::string value;
    std::string sentence;
    std::string debug_string;
    bool debug_bool = false;
    
    HashMap h_main;


    char again = 'Y';
    while (again == 'Y')
    {
        std::cin >> command;
        
        if (command == "DEBUG")
        {
            std::cin >> debug_string;
            
            if (debug_string == "ON")
            {
                if (debug_bool == true)
                {
                    std::cout << "ON ALREADY" << std::endl;
                }
                else if (debug_bool == false)
                {
                    std::cout << "ON NOW" << std::endl;
                }
                debug_bool = true;
            }
            
            else if (debug_string == "OFF")
            {
                if (debug_bool == true)
                {
                    std::cout << "OFF NOW" << std::endl;
                }
                else if (debug_bool == false)
                {
                    std::cout << "OFF ALREADY" << std::endl;
                }
                debug_bool = false;
            }
            
        }
        
        
        
        else if (command == "LOGIN")
        {
            std::cin >> key;
            if (key != "COUNT")
            {
                std::cin >> value;
                if (value == h_main.value(key))
                {
                    std::cout << "SUCCEEDED" << std::endl;
                }
                else
                {
                    std::cout << "FAILED" << std::endl;
                }
            }
            
            else if (key == "COUNT")
            {
                if (debug_bool == true)
                {std::cout << h_main.size() << std::endl;}
                else if (debug_bool == false)
                {std::cout << "INVALID" << std::endl;}
            }
       }
        
        
    
        else if (command == "BUCKET")
        {
            std::cout << h_main.bucketCount() << std::endl;
        }
        
        else if (command == "LOAD")
        {
            std::cout << h_main.loadFactor() << std::endl;
        }
        
        else if (command == "MAX")
        {
            std::cout << h_main.maxBucketSize() << std::endl;
        }
        
        
        
        
       
        else if (command == "CREATE") //FIRST COMMAND
        {
            std::cin >> key;
            std::cin >> value;
        if (h_main.contains(key))
        {

            std::cout << "EXISTS" << std::endl;
        }
        else
        {
        h_main.add(key,value);
            std::cout << "CREATED" << std::endl;
        }
        }

     
    //std::cout << "index = " << result << std::endl;

     else if (command == "REMOVE")
    {
        std::cin >> key;
        if (h_main.contains(key))
        {
            h_main.remove(key);
            std::cout << "REMOVED" << std::endl;
        }
        else
        {
            std::cout << "NONEXISTENT" << std::endl;
        }
    }

        
     else if (command == "CLEAR")
    {
        h_main.clear();
        std::cout << "CLEARED" << std::endl;
    }
     else if (command == "QUIT")
    {
        std::cout << "GOODBYE" << std::endl;
        return 0;
    }
    
    else
    {
        std::cout << "INVALID" << std::endl;
    }

    }
    return 0;
}

