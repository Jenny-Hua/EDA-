// Escribe en el archivo.dot para graficar desde la raiz
    // Siguiendo la secuencia INORDER
    void graphicHelper(ofstream &file, NodePtr root)
    {
        if (root != TNULL)
        {
            graphicHelper(file, root->left);

            // Escribir en el archivo el hijo izq
            if (root->left)
            {
                string color = (root->color) ? "red" : "black";
                file << root->data
                     << "[color=" << color << "]"
                     << "->"
                     << root->left->data << "\n";
            }
            else
            { // Si el hijo izquierdo es NULL pintar de negro
                file << "Null [color=\"black\"]"
                     << "\n";
            }

            // Escribir en el archivo el hijo der
            graphicHelper(file, root->right);

            // Escribir en el archivo el hijo izq
            if (root->right)
            {
                string color = (root->color) ? "red" : "black";
                file << root->data
                     << "[color=" << color << "]"
                     << "->"
                     << root->right->data << "\n";
            }
            else
            { // Si el hijo izquierdo es NULL pintar de negro
                file << "Null [color=\"black\"]"
                     << "\n";
            }

            graphicHelper(file, root->right);
        }
    }

    // Graficar con Graphviz
    void graphic(string inFileDOT) //, string outFilePNG)
    {
        ofstream archivo;
        archivo.open(inFileDOT);
        // string command = "dot -Tpng "+  inFileDOT; //+ " -o " + outFilePNG;
        // const char* c1 = command.c_str();

        if (archivo.is_open())
        {
            archivo << "digraph G { \n";
            archivo << "rankdir=LR\n";
            graphicHelper(archivo, this->getRoot());
            archivo << "}\n";
            archivo.close();
            system("dot -Tpng graph.dot -o graph.png");
        }
        else
        {
            cout << "error al crear archivo";
        }
    };