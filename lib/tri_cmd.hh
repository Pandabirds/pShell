/**
    @file tri_cmd.hh
    The header file that contains the triangle calculator for pShell.
*/

#ifndef PSHELL_LIB_TRI_CMD_HH_
#define PSHELL_LIB_TRI_CMD_HH_

#include <iostream>

namespace tri {
    /**
        @class Triangle
        The Triangle class to be used by the tri command.
    */
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
                Checks if the triangle is right.
                @param[out] is_triangle_right Whether or not it is right.
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
                Updates the triangle's angles and sides using trigonometry.
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
        @fn inline int TriCommandCycle(const int kLayers, Triangle& triangle)
        The function called each time main() wants a command.

        @param[in] kLayers The amount of layers to print out.
        @param[in] triangle The triangle to be used.
        @param[out] exit_code The exit code.
    */
    inline int TriCommandCycle(const int kLayers, Triangle& triangle) {
        return 0;
    }

    /**
        @fn inline int main(const int kLayers)
        The function that starts running the triangle calculator.

        @param[in] kLayers The amount of layers to print at.
        @param[out] exit_code The exit code.
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