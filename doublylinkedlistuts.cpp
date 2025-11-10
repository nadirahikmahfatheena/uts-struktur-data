#include <iostream>
#include <string>

using namespace std;

#define Nil nullptr

typedef string infotype;

struct elmList;

typedef elmList* address;

struct elmList {
    infotype url;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
};

void createList(List &L) {
    L.first = Nil;
    L.last = Nil;
}

address createElmt(infotype data) {
    address p = new elmList;
    p->url = data;
    p->next = Nil;
    p->prev = Nil;
    return p;
}

void insertLast(List &L, infotype data) {
    address p = createElmt(data);
    if (L.first == Nil) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

address cariRiwayat(List L, infotype cari) {
    address p = L.first;
    while (p != Nil) {
        if (p->url == cari) {
            return p;
        }
        p = p->next;
    }
    return Nil;
}

void hapusRiwayat(List &L, infotype data) {
    address p = cariRiwayat(L, data);

    if (p != Nil) {
        if (p == L.first && p == L.last) {
            L.first = Nil;
            L.last = Nil;
        } else if (p == L.first) {
            L.first = p->next;
            L.first->prev = Nil;
        } else if (p == L.last) {
            L.last = p->prev;
            L.last->next = Nil;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        
        delete p;
    }
}

void backward(List L, infotype url) {
    address pCari = cariRiwayat(L, url);

    if (pCari == Nil || L.first == Nil) {
        cout << "proses backward gagal." << endl;
    } else {
        address p = L.last;
        bool stop = false;
        
        while (p != Nil && !stop) {
            cout << "- " << p->url << endl;
            
            if (p == pCari) {
                stop = true;
            }
            
            p = p->prev;
        }
    }
}

void printAll(List L) {
    cout << "riwayat saat ini (Oldest -> Newest)" << endl;
    address p = L.first;
    if (p == Nil) {
        cout << "[riwayat kosong]" << endl;
    }
    while (p != Nil) {
        cout << p->url << endl;
        p = p->next;
    }
    cout << "-----------------------------------------------" << endl;
}

int main() {
    List riwayat;
    createList(riwayat);

    insertLast(riwayat, "https://www.google.com/");
    insertLast(riwayat, "https://chatgpt.com/");
    insertLast(riwayat, "https://outlook.office.com/mail/");
    insertLast(riwayat, "https://igracias.telkomuniversity.ac.id/");

    cout << "list awal:" << endl;
    printAll(riwayat);
    cout << endl;

    cout << "menjalankan backward ke 'https://chatgpt.com/'" << endl;
    backward(riwayat, "https://chatgpt.com/");
    cout << endl;

    cout << "menjalankan backward ke 'https://situs.tidak.ada/'" << endl;
    backward(riwayat, "https://situs.tidak.ada/");
    cout << endl;

    cout << "menghapus 'https://outlook.office.com/mail/' (elemen tengah)" << endl;
    hapusRiwayat(riwayat, "https://outlook.office.com/mail/");
    printAll(riwayat);
    cout << endl;

    cout << "menghapus 'https://www.google.com/' (elemen pertama)" << endl;
    hapusRiwayat(riwayat, "https://www.google.com/");
    printAll(riwayat);
    cout << endl;

    cout << "menghapus 'https://data.tidak.ada'" << endl;
    hapusRiwayat(riwayat, "https://data.tidak.ada");
    printAll(riwayat);
    cout << endl;

    cout << "menghapus dua elemen tersisa" << endl;
    hapusRiwayat(riwayat, "https://igracias.telkomuniversity.ac.id/");
    hapusRiwayat(riwayat, "https://chatgpt.com/");
    printAll(riwayat);
    cout << endl;

    cout << "menjalankan backward di list kosong" << endl;
    backward(riwayat, "https://www.google.com/");
    cout << endl;

    return 0;
}