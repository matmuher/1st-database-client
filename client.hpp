//  #ifndef CLIENT_H - это нужно от двойного включения данного ашника
//  #define CLIENT_H

class Client {
private:
Vehicle*** garage = nullptr; // KK: it is bad way to readable, will be better: using GargeArray = Vehicle***
int size[3]; // MM: magic number, will be better: #define COUNT_STH 3

public:
    void AddElement(Vehicle* a); // KK: a - bad name
    void AddVehicleFromConsole();
    void DeleteElement();
    void CopyElement();
    int GetSize();

    void RestoreFrom(std::fstream& file_stream);
    void WriteElementsTo(std::ostream& output);
    void WriteToFile(std::fstream& file_stream);
    void Menu();

    Client();
};

Client::Client() {
    for (int i = 0; i < 3; i++) { // i - bad name 
        size[i] = 0;
    }
    garage = new Vehicle**[3];
    garage[0] = new Vehicle*[0]; // MM: Why allocate in such way?
    garage[1] = new Vehicle*[0]; // if you wanted to allocate a pointer
    garage[2] = new Vehicle*[0]; // you could just write: new Vehicle*;
}

int Client::GetSize() {
return size[0] + size[1] + size[2]; // if you use tab - use it in every functions
}

/*
    MM: The system is not flexible. I mean when you
    want to change size of garage to 4 you need to find all '3'
    in your code and replace them with '4'. This process is error-prone
    and take time.

    It's better to operate with variable or constant like "garageSize".
*/

// MM: Name doesn't give any information about object.
// 
void Client::AddElement(Vehicle *a) { // element - bad name

    
    /*
        MM: Now your type variable ('m') can get any value
        like 17 or -99. It's error-prone.

        It's better to use more limited type like enum.
        It can get only values that belong to enum.
    */

    int m = -1; // m - bad name
    switch (a->GetType()) { // it will be better create enum class for types 
        case 'e':
            m = 0;
            break;
        case 's':
            m = 1;
            break;
        case 'r':
            m = 2;
            break;
        default:
            std::cout << "[some problem occurred]" << std::endl; // use throw std::logic_error("[some ...]")
            return;
    }

    // MM: Why function AddElement allocates new_garage?
    // One function - one responsibility
    Vehicle** new_garage = new Vehicle*[size[m] + 1]; // MM: Why allocate size+1? Why not just size?
    for (int i = 0; i < size[m]; i++) { // i - bad name
        new_garage[i] = garage[m][i];
    }
    new_garage[size[m]] = a;
    delete[] garage[m];
    garage[m] = new_garage;
    size[m]++;
    std::cout << "[element added]" << std::endl;
}


void Client::AddVehicleFromConsole() {
    std::string brand, model, destination;
    int type, volume, power, landscape, color, sit_pas, max_pas;
    char gearbox;
    // MM: ^---- uninitialized variables:
    // google what kind of error it causes

    std::cout << "What vehicle do you want to add? Bike - 0, Bus - 1, Car - 2: ";
    std::cin >> type;
    std::cin.ignore(); // Ignore the newline character

    /*
        MM: AWFUL COPYPASTE!!!!

        Copypaste is error-prone and unflexible.
        If you need to do some action multiple times - create function:

        like: getProperty(...) etc 
    */
    switch (type) {
        case 0:
            std::cout << "Enter a brand: ";
            std::getline(std::cin, brand);
            if (brand.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a model: ";
            std::getline(std::cin, model);
            if (model.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a volume: ";
            if (!(std::cin >> volume) || volume <= 0) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a power: ";
            if (!(std::cin >> power) || power <= 0) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Landscapes: 1/2/3\nEnter a landscape: ";
            if (!(std::cin >> landscape) || landscape < 1 || landscape > 3) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }

            AddElement(new Bike(brand, model, volume, power, landscape));
            break;

        case 1:
            std::cout << "Enter a brand: ";
            std::getline(std::cin, brand);
            if (brand.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a model: ";
            std::getline(std::cin, model);
            if (model.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a num of sit. pas: ";
            if (!(std::cin >> sit_pas) || sit_pas < 0) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a num of max. pas: ";
            if (!(std::cin >> max_pas) || max_pas < 0 || sit_pas > max_pas) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a destination: ";
            std::cin.ignore();
            std::getline(std::cin, destination);
            if (destination.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }

            AddElement(new Bus(brand, model, sit_pas, max_pas, destination));
            break;

        case 2:
            std::cout << "Enter a brand: ";
            std::getline(std::cin, brand);
            if (brand.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a model: ";
            std::getline(std::cin, model);
            if (model.empty()) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a volume: ";
            if (!(std::cin >> volume) || volume <= 0) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a color[1red, 2blue, 3green, 4black, 5white, 6yellow]: ";
            if (!(std::cin >> color) || color < 1 ||color > 6) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            std::cout << "Enter a gearbox[a/m/r/c]: ";
            if (!(std::cin >> gearbox)) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }
            if ((gearbox != 'a') && (gearbox != 'm') && (gearbox != 'r') && (gearbox != 'c')) {
                std::cout << "[invalid input]" << std::endl;
                return;
            }

            AddElement(new Car(brand, model, volume, color, gearbox));
            break;

        default:
            std::cout << "[invalid input]" << std::endl;
            break;
    }
}

void Client::DeleteElement() {
    int row, element;
    std::cout << "What vehicle do you want to delete? Bike - 0, Bus - 1, Car 2: ";
    std::cin >> row;
    if (!(row >= 0 && row <3)) {
        // MM: If you type error it's better to print more
        // information about this error to fix it quicker.
        // Like print input that you considered incorrect
        std::cout << "[incorrect input]" << std::endl;
        return;
    }

    // MM: It's unreadable. Try to make one action in a line
    std::cout << ((row == 0)?"bikes":((row == 1)?"buses":"cars")) << ':' << std::endl;
    for (int i = 0; i != size[row]; i++) {
        std::cout << '#' << i << " - " << garage[row][i] << std::endl;
    }
    std::cout << "Which one do you want to delete?" << std::endl;
    std::cin >> element;
    if (!(element >= 0 && element < size[row])) {
        std::cout << "[incorrect input]" << std::endl;
        return;
    }
        if (row >= 0 && row < 3 && element >= 0 && element < size[row]) {
            Vehicle** new_garage = new Vehicle*[size[row] - 1];
            int newIndex = 0;
            for (int i = 0; i < size[row]; i++) {
                if (i != element) {
                    new_garage[newIndex] = garage[row][i];
                    newIndex++;
                }
            }
            delete[] garage[row];
            garage[row] = new_garage;
            size[row]--;
            std::cout << "[element deleted]" << std::endl;
        }
        else {
            std::cout << "[invalid row or element number - deleting hasn't proceed]" << std::endl;
        }
}

void Client::CopyElement()
{
    int row, element;
    std::cout << "What vehicle do you want to copy? Bike - 0, Bus - 1, Car 2: ";
    std::cin >> row;
    if (!(row >= 0 && row <3)) {
        std::cout << "[incorrect input]" << std::endl;
        return;
    }
    std::cout << ((row == 0)?"bikes":((row == 1)?"buses":"cars")) << ':' << std::endl;
    for (int i = 0; i != size[row]; i++) {
        std::cout << i << " - " << garage[row][i] << std::endl;
    }
    std::cout << "Which one do you want to copy?" << std::endl;
    std::cin >> element;
    if (!(element >= 0 && element < size[row])) {
        std::cout << "[incorrect input]" << std::endl;
        return;
    }
    AddElement(garage[row][element]);
};

void Client::WriteElementsTo(std::ostream& output) {
    for (int i = 0; i < 3; i++) {
        for (int n = 0; n < size[i]; n++) {
            output << '-'<< ((i == 0)?"bike":((i == 1)?"bus":"car")) << ":" << std::endl << garage[i][n] << std::endl;
        }
        output << std::endl;
    }
    std::cout << "[written]" << std::endl;
}

void Client::RestoreFrom(std::fstream& file_stream) {
    std::string line, vehicleType, skip;
    while (std::getline(file_stream, line)) {
        if (line == "-bike:") {
            std::string brand, model;
            int engineVolume, power, landscape;


            // MM: Do u really need so much nested 'ifs'?
            // Copypaste in reading and matching line
            if ((std::getline(file_stream, line)) && (line == "Brand:")) {
                std::getline(file_stream, brand);
                if ((std::getline(file_stream, line)) && (line == "Model:")) {
                    std::getline(file_stream, model);
                    if ((std::getline(file_stream, line)) && (line == "Engine Volume:")) {
                        std::getline(file_stream, skip);
                        engineVolume = stoi(skip);
                        if (engineVolume < 0) {
                            std::cout << "[incorrect volume]" << std::endl;
                        } else
                        if ((std::getline(file_stream, line)) && (line == "Power:")) {
                            std::getline(file_stream, skip);
                            power = stoi(skip);
                            if (power < 0) {
                                std::cout << "[incorrect power]" << std::endl;
                            } else
                            if ((std::getline(file_stream, line)) && (line == "Landscape:")) {
                                std::getline(file_stream, skip);
                                landscape = stoi(skip);
                                if (landscape < 0 || landscape > 3) {
                                    std::cout << "[incorrect landscape]" << std::endl;
                                } else
                                AddElement(new Bike(brand, model, engineVolume, power, landscape));
                            }
                        }
                    }
                }
            }
        } else if (line == "-bus:") {
            std::string brand, model, destination;
            int sittingPassengers, maxPassengers;
            if ((std::getline(file_stream, line)) && (line == "Brand:")) {
                std::getline(file_stream, brand);
                if ((std::getline(file_stream, line)) && (line == "Model:")) {
                    std::getline(file_stream, model);
                    if ((std::getline(file_stream, line)) && (line == "Sit. passangers:")) {
                        std::getline(file_stream, skip);
                        sittingPassengers = stoi(skip);
                        if (sittingPassengers < 0) {
                            std::cout << "[incorrect num of sit.pas.]" << std::endl;
                        } else
                        if ((std::getline(file_stream, line)) && (line == "Max. passangers:")) {
                            std::getline(file_stream, skip);
                            maxPassengers = stoi(skip);
                            if (sittingPassengers < 0 || sittingPassengers > maxPassengers) {
                                std::cout << "[incorrect num of max.pas.]" << std::endl;
                            } else
                            if ((std::getline(file_stream, line)) && (line == "Destination:")) {
                                std::getline(file_stream, destination);
                                AddElement(new Bus(brand, model, sittingPassengers, maxPassengers, destination));
                            }
                        }
                    }
                }
            }
        } else if (line == "-car:") {
            std::string brand, model;
            int engineVolume, color;
            char gearbox;
            if ((std::getline(file_stream, line)) && (line == "Brand:")) {
                std::getline(file_stream, brand);
                if ((std::getline(file_stream, line)) && (line == "Model:")) {
                    std::getline(file_stream, model);
                    if ((std::getline(file_stream, line)) && (line == "Engine Volume:")) {
                        std::getline(file_stream, skip);
                        engineVolume = stoi(skip);
                        if (engineVolume < 0) {
                            std::cout << "[incorrect volume]" << std::endl;
                        } else
                        if ((std::getline(file_stream, line)) && (line == "Color:")) {
                            std::getline(file_stream, skip);
                            color = stoi(skip);
                            if (color < 1 || color > 6) {
                                std::cout << "[incorrect color]" << std::endl;
                            } else
                            if ((std::getline(file_stream, line)) && (line == "Gearbox:")) {
                                std::getline(file_stream, skip);
                                gearbox = skip[0];
                                if ((gearbox != 'a') && (gearbox != 'm') && (gearbox != 'r') && (gearbox != 'c')) {
                                    std::cout << "[incorrect gearbox]" << std::endl;
                                } else
                                AddElement(new Car(brand, model, engineVolume, color, gearbox));
                            }
                        }
                    }
                }
            }
        }
    }
}

void Client::Menu()
{
    std::fstream file("file.txt", std::ios::in | std::ios::out); // MM: check for correct open?
    int x = 0;
    while (x != 7)
    {
        std::cout << "1. Add vehicle" << std::endl;
        std::cout << "2. Delete vehicle" << std::endl;
        std::cout << "3. Show garage" << std::endl;
        std::cout << "4. Copy element" << std::endl;
        std::cout << "5. Save to file" << std::endl;
        std::cout << "6. Restore from file" << std::endl;
        std::cout << "7. Exit" << std::endl;
        if (!(std::cin >> x) || x > 7 || x < 1 )
        {
            std::cout << "[incorrect. try again]" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            switch (x) {
                case 1:
                    AddVehicleFromConsole();
                    break;
                case 2:
                    DeleteElement();
                    break;
                case 3:
                    WriteElementsTo(std::cout);
                    break;
                case 4:
                    CopyElement();
                    break;
                case 5:
                {
                    if (file.is_open())
                    {
                        file.seekp(0);
                        WriteElementsTo(file);
                        std::cout << "[data saved to out.txt]" << std::endl;
                    }
                    else
                    {
                        std::cout << "[unable to save]" << std::endl;
                    }
                }
                    break;
                case 6:
                    RestoreFrom(file);
                    std::cout << "[restored]" << std::endl;
                    break;
                    
                default:
                    break;
            }
        }
    }
    std::cout << "[exiting... Do you want to save to file?\n1 - yes, 2/other - no]" << std::endl;
    std::cin >> x;
    if (x == 1)
    {
        if (file.is_open())
        {
            file.seekp(0);
            WriteElementsTo(file);
            std::cout << "[data saved to out.txt]" << std::endl;
        }
        else
        {
            std::cout << "[unable]" << std::endl;
        }
    }
    file.close();
    std::cout << "[exit done]" << std::endl;
};

// #endif - можешь попробовать без этого, напиши ответным письмом что будет
