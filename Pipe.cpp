#include "Pipe.h"

Pipe::Pipe() : id(0), name(""), length(0.0f), diameter(0), status(false) {}

Pipe::Pipe(int pipeId, const std::string& n, float l, int d)
    : id(pipeId), name(n), length(l), diameter(d), status(false) {
}

bool Pipe::switchStatus(int o) {
    if (o == 1) {
        status = true;
        return true;
    }
    else if (o == 2) {
        status = false;
        return true;
    }
    else {
        return status;
    }
}

void Pipe::displayInfo() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Length: " << length << "\n";
    std::cout << "Diameter: " << diameter << "\n";
    std::cout << "Status: " << (status ? "Under renovation" : "Working") << "\n\n";
}

std::ostream& operator<<(std::ostream& out, const Pipe& p) {
    out << p.id << "\n";
    out << p.name << "\n";
    out << p.length << "\n";
    out << p.diameter << "\n";
    out << p.status << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Pipe& p) {
    in >> p.id;
    in.ignore();
    std::getline(in, p.name);
    in >> p.length;
    in >> p.diameter;
    in >> p.status;
    return in;
}