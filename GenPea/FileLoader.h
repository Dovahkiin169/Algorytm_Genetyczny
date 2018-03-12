#ifndef FILELOADER_H
#define FILELOADER_H

#include "Nodes.h"

bool loadFile(string filename, Nodes *nodesArr);

Nodes *convFromOldTSPtoATSP(Nodes *nodesArr);

#endif //FILELOADER_H
