#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// ��������� ��� ���������� � �����
class IDocument {
public:
    virtual ~IDocument() = default;
    virtual std::string GetName() const = 0;
    virtual void Display() const = 0;
};

// ����� ��� ��������� ����������
class Document : public IDocument {
private:
    std::string name;

public:
    Document(const std::string& name) : name(name) {}

    std::string GetName() const override {
        return name;
    }

    void Display() const override {
        std::cout << "Document: " << name << std::endl;
    }
};

// ����� ��� �����, ���������� ��������� � ������ �����
class Folder : public IDocument {
private:
    std::string name;
    std::vector<IDocument*> documents;

public:
    Folder(const std::string& name) : name(name) {}

    ~Folder() {
        for (auto document : documents) {
            delete document;
        }
    }

    std::string GetName() const override {
        return name;
    }

    void Add(IDocument* document) {
        documents.push_back(document);
    }

    void Remove(IDocument* document) {
        documents.erase(std::remove(documents.begin(), documents.end(), document), documents.end());
    }

    void Display() const override {
        std::cout << "Folder: " << name << std::endl;
        for (const auto& document : documents) {
            document->Display();
        }
    }
};

// ������ �������������
int main() {
    // �������� ��������� ����������
    IDocument* doc1 = new Document("Invoice.pdf");
    IDocument* doc2 = new Document("Report.docx");
    IDocument* doc3 = new Document("Photo.jpg");

    // �������� ����� � ���������� � ��� ����������
    Folder* folder1 = new Folder("Work Documents");
    folder1->Add(doc1);
    folder1->Add(doc2);

    // �������� ������ ����� � ���������� � ��� ����������
    Folder* folder2 = new Folder("Personal Files");
    folder2->Add(doc3);

    // �������� �������� ����� � ���������� � ��� ������ ����� � ����������
    Folder* rootFolder = new Folder("Root");
    rootFolder->Add(folder1);
    rootFolder->Add(folder2);
    rootFolder->Add(new Document("Readme.txt"));

    // ����������� ����������� ���� �������� ���������
    rootFolder->Display();

    // ������� ������
    delete rootFolder;

    return 0;
}
