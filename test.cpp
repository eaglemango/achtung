#include <filesystem>
#include <iostream>
#include <string>

#include "achtung.hpp"

int GenerateFd() {
    // К сожалению, файловых дескрипторов никогда нет
    THROW(AchtungType::FD_LIMIT);

    return 42;
}

int Open(const std::string& filepath) {
    // Программа не умеет обрабатывать длинные названия
    if (filepath.size() > 15) {
        THROW(AchtungType::MEMORY);
    }

    // Проверим существование файла
    if (!std::filesystem::exists(filepath)) {
        THROW(AchtungType::DOES_NOT_EXIST);
    }

    int fd = GenerateFd();

    // Тут что-то должно происходить

    return fd;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No file chosen" << std::endl;

        return 1;
    }

    TRY({
        int fd = Open(argv[1]);
        std::cout << "Got fd: " << fd << std::endl;
    })
    CATCH(AchtungType::DOES_NOT_EXIST, {
        std::cout << "File " << argv[1] << " does not exist" << std::endl;
    })
    CATCH(AchtungType::FD_LIMIT, {
        std::cout << "No more file descriptors available" << std::endl;
    })
    FAIL_IF_UNCAUGHT

    return 0;
}
