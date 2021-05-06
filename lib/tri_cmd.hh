/**
    @file tri_cmd.hh
    @brief The header file that contains the triangle calculator for pShell.
    
    @namespace tri
    @brief The set of functions used by the triangle calculator to function.
        @class Triangle
        @brief A class used to store the basic information of triangles.
            @public
                double angle1_
                double angle2_
                double angle3_
                double side1_
                double side2_
                double side3_

                @fn void UpdateTriangle(void)
                @brief Updates the triangle's angles and sides using trigonometry.
    
    @fn int TriCommandCycle(const int kLayers, Triangle& triangle)
    @brief The function called each time man() wants a command.
    
    @fn int main(const int kLayers)
    @brief The function that starts running the triangle calculator.
*/

#ifndef PSHELL_LIB_TRI_CMD_HH_
#define PSHELL_LIB_TRI_CMD_HH_

#include <iostream>

namespace tri {
    class Triangle {
        public:
            double angle1_ = -1.0;
            double old_angle1_ = -2.0;
            double angle2_ = -1.0;
            double old_angle2_ = -2.0;
            double angle3_ = -1.0;
            double old_angle3_ = -2.0;

            double side1_ = -1.0;
            double old_side1_ = -2.0;
            double side2_ = -1.0;
            double old_side2_ = -2.0;
            double side3_ = -1.0;
            double old_side3_ = -2.0;

            /**
             * Checks if the triangle is right.
             * @return Whether or not it is right.
             */
            bool IsRight(void) {
                return angle1_ == 90 || angle2_ == 90 || angle3_ == 90;
            }
            //TODO: finish this whole calc
            //TODO: #1 fix the "old" system

            bool HasBeenChanged(void) {
                bool out = false;

                if (angle1_ != old_angle1_ || angle2_ != old_angle2_ || angle3_ != old_angle3_) {
                    out = true;
                }

                if (side1_ != old_side1_ || side2_ != old_side2_ || side3_ != old_side3_) {
                    out = true;
                }

                return out;
            }

            /**
             * Updates the triangle's angles and sides using trigonometry.
             */
            void UpdateTriangle(void) {
                while (HasBeenChanged()) {
                    bool angle1_known = angle1_ != -1.0;
                    bool angle2_known = angle2_ != -1.0;
                    bool angle3_known = angle3_ != -1.0;

                    bool side1_known = side1_ != -1.0;
                    bool side2_known = side2_ != -1.0;
                    bool side3_known = side1_ != -1.0;
                }
            }
    };

    /**
     * The function called each time main() wants a command.
     * 
     * @param kLayers The amount of layers to print out.
     * @param triangle The triangle to be used.
     * @return The return value.
     */
    inline int TriCommandCycle(const int kLayers, Triangle& triangle) {
        return 0;
    }

    /**
     * The function that starts running the triangle calculator.
     * 
     * @return The exit code.
     */
    inline int main(const int kLayers) {
        std::cout << "-TRI-" << '\n';

        Triangle triangle;
        while (true) {
            // Good opportunity for a pun.
            TriCommandCycle(kLayers, triangle);
        }

        std::cout << "-TRI-" << '\n';
        return 0;
    }
}

#endif