#include <iostream>
#include <utility>
#include <algorithm>
#include <locale>

#include "queue.h"
#include "rectangle.h"
#include "vertex.h"
#include "vector.h"


void printHelp() {
    std::cout << std::endl << "'1'           - Add" << std::endl;
    std::cout << "'2'           - Remove" << std::endl;
    std::cout << "'3'           - Print" << std::endl;
    std::cout << "'4'           - Front" << std::endl;
    std::cout << "'5'           - Back" << std::endl;
    std::cout << "'6'           - Count if" << std::endl;
    std::cout << "'7'           - Exit" << std::endl;
}

int main() {
	Queue<Rectangle<int>> q;
	int cmd, i, cnt;
	double area;

	while (true) {
    	printHelp();
		std::cin >> cmd;
		switch(cmd) {
            case 1: {
			    std::cout << "Add item back of queue or iterator position" << std::endl;
			    std::cout << "command: 1 - <Push> or 2 - <Insert>" << std::endl;
			    std::cin >> cmd;
                if(cmd == 1) {
                    Rectangle<int> rec;
				    std::cout << "push --> Input points: ";
                    try {
					    std::cin >> rec;
		            } catch (std::exception &e) {
					    std::cout << e.what() << std::endl;
					    break;
				    }
					q.Push(rec);
					continue;
                }
			    else if (cmd == 2) {
					Rectangle<int> rec;
					std::cout << "insert --> Input points: ";
					try {
						std::cin >> rec;
					} catch (std::exception &e) {
						std::cout << e.what() << std::endl;
						break;
					}
					std::cout << "       --> Input index: ";
					std::cin >> i;
					Queue<Rectangle<int>>::ForwardIterator it = q.Begin();
					for (cnt = 0; cnt < i; cnt++) {
						it++;
					}
					q.Insert(it, rec);
					continue;
				}
				else {
					std::cout << "[Error 1] Invalid input" << std::endl;
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					break;
				}
			}
			case 2: {
				std::cout << "Delete item from front queue or iterator position" << std::endl;
			    std::cout << "command: 1 - <Pop> or 2 - <Erase>" << std::endl;
				std::cin >> cmd;
				if (cmd == 1) {
					std::cout << "pop -->";
					q.Pop();
					continue;
				}
				else if(cmd == 2) {
					std::cout << "erase --> Input index: ";
					std::cin >> i;
					Queue<Rectangle<int>>::ForwardIterator it = q.Begin();
					for (cnt = 0; cnt < i; cnt++) {
						it++;
					}
					q.Erase(it);
					continue;
				}
				else {
					std::cout << "[Error 2] Invalid input" << std::endl;
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					break;
				}
			}
			case 3: {
				std::cout << "print -->" << std::endl;
				q.Print();
				continue;
			}
			case 4: {
				std::cout << "front --> ";
				Rectangle<int> value;
				try {
					value = q.Front();
				} catch (std::exception &e) {
					std::cout << e.what() << std::endl;
					break;
				}
				std::cout << value << std::endl;
				continue;
			}
		 	case 5: {
				std::cout << "back --> ";
				Rectangle<int> value;
				try {
					value = q.Back();
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
					break;
				}
				std::cout << value << std::endl;
				continue;
			}
			case 6: {
				std::cout << "area --> Input area: ";
				std::cin >> area;
				std::cout << "The number figures with area less than given "
					<< std::count_if(q.Begin(), q.End(), [area](Rectangle<int> t){
					return Area(t) < area;
				}) << std::endl;
				continue;
			}
			case 7: {
				return 0;
			}
			default: {
				std::cout << "[Error 3] Invalid input" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
			}
		}
	}
	return 0;
}
