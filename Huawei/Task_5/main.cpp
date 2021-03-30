#include <iostream>
#include "PacketManager.h"


int main() {
    //Тест на цикл
    PacketManager packetManager = PacketManager("requiredTest.txt", "currentTest.txt");
    if (packetManager.thereIsCycle() == "There is cycle\n")
        cout << "Cycle was found" << endl;
    else {
        cout << "Wrong answer" << endl;
        exit(-1);
    }

    if (packetManager.getMissingDependencies() == "Missing Dependencies:\n"
                                                  "hadoop-yarn -> hadoop-core -> apache-commons\n"
                                                  "hadoop-yarn -> hadoop-core\n"
                                                  "hadoop-yarn -> hadoop-core -> apache-commons -> packet\n"
                                                  "hadoop-yarn -> hadoop-core -> apache-commons -> packet -> this\n")
        cout << "All missing dependencies was found" << endl;
    else {
        cout << "Wrong answer" << endl;
        exit(-1);
    }

    if (packetManager.getExcessDependencies() == "Excess dependencies:\n"
                                                 "-hadoop-hdfs\n")
        cout << "All excess dependencies was found" << endl;
    else {
        cout << "Wrong answer" << endl;
        exit(-1);
    }
    if (packetManager.getDependenciesTree("this") == "hadoop-yarn -> hadoop-core -> apache-commons -> packet -> this\n")
        cout << "Dependencies tree ok" << endl;
    else {
        cout << "Wrong answer" << endl;
        exit(-1);
    }
    if (packetManager.getDependenciesTree("hadoop-yarn") == "hadoop-yarn\n")
        cout << "Dependencies tree ok" << endl;
    else {
        cout << "Wrong answer" << endl;
        exit(-1);
    }

    cout << "Test ok" << endl;
    return 0;
}
