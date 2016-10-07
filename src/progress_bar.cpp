#include <iostream>

class progress_bar {
    private:
        int width;
        int N;
        int x;
    public:
        progress_bar(int width, int total) {
            this->width = width;
            this->N = total;
            x = 0;
        }
        void do_progress() {
            float progress = ++x / (double) N;
            int pos = width * progress;
            std::cout << "[";
            for (int i = 0; i < width; ++i) {
                if (i < pos) std::cout << "=";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << " %\r";
            std::cout.flush();
        }
        ~progress_bar() {
            std::cout << std::endl;
        }
};
