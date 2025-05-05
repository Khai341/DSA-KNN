#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

/////
template<typename T>
class SList : public List<T> {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(T data) {
            this->data = data;
            next = nullptr;
        }
    };
    int number;
    Node* head;
    Node* tail;
    T data;
public:
    SList() :List<T>() {
        head = nullptr;
        tail = nullptr;
        number = 0;
    };
    ~SList() {
        if (head == nullptr) return;
        Node* runner = head;
        while (runner != nullptr) {
            Node* temp = runner->next;
            delete (runner);
            runner = temp;
        }
    };
    void push_back(T value) {
        if (head == nullptr || number == 0) {
            Node* newNode = new Node(value);
            head = newNode;
            tail = newNode;
            number = 1;
            return;
        }
        tail->next = new Node(value);
        tail = tail->next;
        number++;
        return;
    };
    void push_front(T value) {
        if (head == nullptr || number == 0) {
            Node* newNode = new Node(value);
            head = newNode;
            tail = newNode;
            number = 1;
            return;
        }
        Node* temp = head;
        Node* newNode = new Node(value);
        head = newNode;
        head->next = temp;
        number++;
        return;
    };
    void insert(int index, T value) {
        Node* runner = head;
        // 12/3 (2:37)
        if (index < 0) return;
        if (index == 0) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            number++;
            return;
        }
        //
        while (runner != nullptr) {
            if (index == 1 || runner->next == nullptr) {//12/3 (2:37)
                Node* newNode = new Node(value);
                newNode->next = runner->next;
                runner->next = newNode;
                number++;
                return;
            }
            index--;
            runner = runner->next;
        }
        return;
    };
    void remove(int index) {
        if (index < 0 || index >= number) return;
        number--;// 12/3
        if (index == 0) {//head cannot null
            Node* temp = head;
            head = head->next;
            free(temp);
            return;
        }
        if (index == number - 1) {
            Node* runner = head;
            while (runner->next != tail) {
                runner = runner->next;
            }
            free(tail);
            tail = runner;
            tail->next = nullptr;//
            return;
        }
        Node* runner = head;
        while (runner != nullptr) {
            if (runner->next == nullptr) return;
            if (index == 1 || runner->next == nullptr) {
                Node* temp = runner->next->next;//runner->next cannot be null
                free(runner->next);
                runner->next = temp;
                return;
            }
            index--;
            runner = runner->next;
        }
        return;
    };
    T& get(int index) const {
        if (index < 0 || index >= number) throw std::out_of_range("get(): Out of range");
        Node* runner = head;
        while (runner != nullptr) {
            if (index == 0 || runner->next == nullptr) {
                return runner->data;
            }
            runner = runner->next;
            index--;
        }
        return head->data;//fall case;
    };
    int length() const { return number; };
    void clear() {
        Node* runner = head;
        while (runner != nullptr) {
            Node* temp = runner->next;
            runner = runner->next;
            free(temp);
        }
        return;
    };
    void print() const {
        Node* runner = head;
        while (runner != nullptr) {
            cout << runner->data;
            if (runner->next != nullptr) cout << " ";
            //cout << " ";
            runner = runner->next;
        }
        cout << endl;
        return;
    };
    void reverse(Node*& runner = nullptr) {/*
        if (runner == nullptr) {
            reverse(head);
            return;
        }
        if (runner->next == nullptr) {
            head = runner;
            return;
        }
        Node* runner1 = runner;
        Node* runner2 = runner;
        reverse(runner2->next);
        //
        runner2->next = runner1;
        runner1->next = nullptr; tail = runner1;*/
        return;
    };
    void reverse() {
        //reverse(head);
        return;
    }
    ///////////////////////////per down below
    Node* returnhead() {
        return head;
    }
    void print(int s_idx, int e_idx) {
        Node* runner = head;
        int idx = 0;
        while (runner != nullptr) {
            if (idx >= s_idx && idx <= e_idx) {
                cout << get(idx);//<<" ";
                if (idx != e_idx && runner->next != nullptr) cout << " ";
            }
            idx++;

            if (runner->next == nullptr) return;
            runner = runner->next;
        }
        return;
    }
    bool Sll_return_idx(T data, int& out) {
        Node* runner = head;
        int run_idx = 0;
        while (runner != nullptr) {
            if (runner->data == data) {
                out = run_idx;
                return true;
            }
            runner = runner->next;
            run_idx++;
        }
        return false;
    }


};
/////
bool is_number(string s) {
    if (s.size() == 0)return false;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' ||
            s[i] == '8' || s[i] == '9' || s[i] == '\r' || s[i] == '\n');
        else return false;
    }
    return true;
}
bool per_create(string name_file, SList < SList <int >* >*& data, SList <string >*& label, int& rows, int& cols) {
    ifstream myfile; myfile.open(name_file);
    string mystring;
    int loop_out = 0;
    if (!myfile.is_open()) return false;//
    while (myfile.good()) {
        string out0;
        myfile >> out0;
        if (out0 == "") continue;// safe guard when there is an epy line
        stringstream ss(out0);
        string out;
        int loop_in = 0;
        SList<int>* temp = new SList<int>();
        while (ss.good())
        {
            loop_in++;
            getline(ss, out, ',');

            if (loop_out == 0)
            {
                label->push_back(out);
            }

            else
            {
                if (is_number(out))temp->push_back(stoi(out));
                else return false;
            }
        }
        if (loop_out != 0) {

            data->push_back(temp);
        }
        loop_out++;

        cols = loop_in;
        if (loop_in != 785) return false;//785 is 28*28+1
    }
    rows = loop_out - 1;

    return true;
}

void per_deep_copy(SList<SList<int>*>*& data, SList<string>*& label, SList<SList<int>*>* data_source, SList<string>* label_source,
    int& cols, int& rows, int cols_s, int rows_s) {
    // free(data);
    // free(label);
    cols = cols_s;
    rows = rows_s;
    data = new SList<SList<int>*>;
    label = new SList<string>;
    for (int i = 0; i < cols_s; i++) {
        label->push_back(label_source->get(i));
    }
    for (int i = 0; i < rows_s; i++) {
        SList<int>* temp_out = new  SList<int>;
        SList<int>* temp_in = data_source->get(i);
        for (int j = 0; j < cols_s; j++) {
            temp_out->push_back(temp_in->get(j));
        }
        data->push_back(temp_out);
    }
    return;
}


class Dataset {
private:
    // List < List <int >* >* data ;
    SList<SList<int>*>* data;
    SList<string>* label;
    int rows;
    int cols;
public:
    SList<string>* per_get_label() {
        return label;
    }
    SList<SList<int>*>* per_get_data_const()const {
        return data;
    }
    SList<SList<int>*>* per_get_data() {
        return data;
    }


    Dataset() {
        data = new SList<SList<int>*>();
        label = new SList<string>();
        rows = 0;
        cols = 0;
    };
    Dataset(SList<SList<int>*>* data, SList<string>* label = nullptr, int rows_in = 0, int cols_in = 0) {
        this->data = data;
        if (label == nullptr)label = new SList<string>();
        else this->label = label;
        rows = rows_in;
        cols = cols_in;
    }
    // ∼Dataset () = default;
    Dataset(const Dataset& other) {
        Dataset();
        per_deep_copy(this->data, this->label, other.data, other.label, this->cols, this->rows, other.cols, other.rows);
        // this->label->print();
        // this->data = other.data;
        // this->label = other.label;
        // this->rows = other.rows;
        // this->cols = other.cols;
    };
    Dataset& operator =(const Dataset& other) {
        this->data = other.data;
        this->label = other.label;
        this->rows = other.rows;
        this->cols = other.cols;
        return *this;
    };
    bool loadFromCSV(const char* fileName) {
        return per_create(fileName, data, label, rows, cols);
    };
    void printHead(int nRows = 5, int nCols = 5) const {
        cout << "enter head   " << rows<<endl;
        if (nRows < 0 || nCols < 0) return;
        label->print(0, nCols - 1);
        cout << endl;
        for (int i = 0; i < nRows; i++) {
            if (i == rows) break;
            SList<int>* row = data->get(i);
            row->print(0, nCols - 1);// also add to csv; code to upgrade rows, and cols
            if (i != nRows - 1 && i+1 != rows) cout << endl;// 12/3 (2:37)
        }
        return;
    };
    void printTail(int nRows = 5, int nCols = 5) const {
        cout << "enter tail" << endl;
        if (nRows < 0 || nCols < 0) return;
        label->print(cols - nCols, cols-1);
        cout << "\n";
        // for (int i=rows-1;i>=rows-nRows;i--){//reverse order of rows
        //     if (i==-1) break;
        //     SList<int>* row = data->get(i);
        //     row->print(cols-nCols,cols);
        //     cout<<endl;
        // }

        for (int i = (rows - nRows >= 0) ? rows - nRows : 0; i <= rows - 1; i++) {
            // if (i==-1) break;
            SList<int>* row = data->get(i);
            row->print(cols - nCols, cols-1);
            if (i != rows - 1)cout << "\n";
            //else cout << "\b";
            //cout << endl;
        }

        //return;
    };
    void getShape(int& nRows, int& nCols) const { nRows = rows; nCols = cols; return; };
    void columns() const { label->print(); };
    bool drop(int axis = 0, int index = 0, std::string columns = "") {
        if (axis == 0) {
            if (index >= rows || index < 0) return false;
            data->remove(index);
            rows--;
            return true;
        }
        else if (axis == 1) {// fix remove func of Slist
            int idx;
            bool bol = label->Sll_return_idx(columns, idx);
            if (bol == false) return false;
            label->remove(idx);

            int data_col = rows - 1;
            while (data_col >= 0) {
                SList<int>* row = data->get(data_col);
                row->remove(idx);
                data_col--;
            }
            cols--;//
            return true;
        }
        else return false;
    };
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int
        endCol = -1) const {
        if (endRow == -1)endRow = rows - 1;
        if (endCol == -1)endCol = cols - 1;
        Dataset out_data(*this);//return out_data;
        // out_data.drop(endRow+1,rows);//drop for rows, need to preview



        // SList<string>* out_label = out_data.per_get_label();
        // while (startCol<=endCol){
        //     string out_string = out_label->get(endCol);
        //     out_data.drop(1,0,out_string);

        //     endCol--;
        // }
        for (int i = rows - 1; i >= 0; i--) {
            if (i >= startRow && i <= endRow) {
                ;
            }
            else out_data.drop(0, i, "");
        }

        SList<string>* out_label = out_data.per_get_label();
        for (int i = cols - 1; i >= 0; i--) {
            if (i >= startCol && i <= endCol) {
                ;
            }
            else out_data.drop(1, 0, out_label->get(i));
        }
        return out_data;
    };
    List < List <int >* >* getData() const {
        List<SList<int>*>* temp1 = data;
        List < List <int >* >* out = reinterpret_cast<List < List <int >* >*>(temp1);
        return out;
    }
};

void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset&
    X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {

    int t1, t2;
    y.getShape(t1, t2);
    cout<<t1<<" "<<t2<<" "<< test_size<<endl;//t1 is larger; t2=1
    //y.printHead();
    // X_test = X.extract(0, round(t1 * test_size)-1, 0, -1);
    // X_train = X.extract(round(t1 * test_size), -1, 0, -1);
    // y_test = y.extract(0, round(t1 * test_size)-1, 0, -1);
    // y_train = y.extract(round(t1 * test_size), -1, 0, -1);

    //X_train = X.extract(0, (int)(t1 - round(t1 * test_size)) - 1, 0, -1);//round
    //X_test = X.extract(t1 - round(t1 * test_size), -1, 0, -1);
    //y_train = y.extract(0, (int)(t1 - round(t1 * test_size)) - 1, 0, -1);//round
    //y_test = y.extract(t1 - round(t1 * test_size), -1, 0, -1);
    X_train = X.extract(0, (int)(t1 - floor(t1 * test_size))-2 , 0, -1);//round
    X_test = X.extract(t1 - floor(t1 * test_size)-1, -1, 0, -1);
    y_train = y.extract(0, (int)(t1 - floor(t1 * test_size))-2 , 0, -1);//round
    y_test = y.extract(t1 - floor(t1 * test_size)-1, -1, 0, -1);
    return;
}
// class per_sorting_sll{
//     public:
//     class Node{
//         int idx;
//         long long int sum;
//         Node*next;
//         Node(){};
//         Node(int idx, long long int sum){
//             this->index = index;
//             this->sum = sum;
//             this->next = nullptr;
//         }
//     }
//     Node* head;
//     Node* tail;
//     int numbers;
//     per_sorting_sll(){
//         head=nullptr;
//         tail=nullptr;
//         numbers=0;
//     }
//     void push_sll (int idx, long long int sum){
//         if (head==nullptr){
//             Node* newNode = new Node (idx,sum);
//             return;
//         }
//         Node*runner = head;
//         while (runner!=nullptr){
//             if (runner->next==nullptr){
//                 return;
//             }
//             if (runner->next->sum > sum){
//                 Node* newNode =  new Node (idx,sum);
//             }
//         }
//     }
// }
void per_add_array(int* arr_idx, int* arr_sum, int k, int idx_add, int sum_add) {
    if (k <= 0) return;
    // if (arr_idx[0]==-1){
    //     arr_idx[0] = idx_add;
    //     arr_sum[0] = sum_add;
    //     return;
    // }
    int max_glob_idx = -1;
    int max_glob_sum = -1;
    for (int i = 0; i < k; i++) {
        if (arr_sum[i] == -1) { max_glob_idx = i; break; }
        if (arr_sum[i] > max_glob_sum || max_glob_sum == -1) {
            max_glob_sum = arr_sum[i];
            max_glob_idx = i;
            //break;
        }
    }
    if (max_glob_idx == -1) return;
    if (sum_add >= max_glob_sum && max_glob_sum != -1) return;
    else {
        arr_idx[max_glob_idx] = idx_add;
        arr_sum[max_glob_idx] = sum_add;
        return;
    }
}

class per_for_knn {
public:

    class Node {
    public:
        long long int sum;
        int idx;
        Node* next;
        Node(long long int sum = 0, int idx = 0) {
            this->sum = sum;
            this->idx = idx;
        }
    };
    Node* head;
    Node* tail;
    Node* max;
    long long max_sum;
    int max_idx;
    int number;
    int max_number;
    void clear() {
        head = nullptr;
        tail = nullptr;
        max = nullptr;
        max_idx = 0;
        max_sum = 0;
        number = 0;
    }
    void print() {
        Node* runner = head;
        while (runner != nullptr) {
            cout << runner->idx << " " << runner->sum << endl;
            runner = runner->next;
        }
        return;
    }
    int get_idx() {
        int temp[10]{ 0 };//14/3
        int idx_return = -1;
        Node* runner = head;
        //cout<< endl;
        while (runner != nullptr) {
            if (max != nullptr && runner == max) {
                //cout << "enter ???" << endl;
                runner = runner->next;
                continue;
            }
            //cout << runner->sum << ","<< runner->idx<<endl;
            if (runner->idx >= 0 && runner->idx <= 9) {
                temp[runner->idx]++;
                if (idx_return == -1) idx_return = runner->idx;
                else {
                    if (temp[runner->idx] == temp[idx_return] && idx_return > runner->idx) idx_return = runner->idx;///////18/3
                    else if (temp[runner->idx] > temp[idx_return]) idx_return = runner->idx;
                }
            }
            runner = runner->next;
        }
        //cout  << endl;
        return (idx_return == -1) ? 0 : idx_return;
    }
    void push_back(Node value) {
        if (number > max_number) {// 14/3
            if (head == nullptr) return;
            if (max_sum < value.sum || (max_sum==value.sum&&max->idx<=value.idx)) return;//max_sum < value.sum
            // cout<<"enter"<<endl;

            Node* runner = head;
            max->sum = value.sum;
            max->idx = value.idx;
            // max = head;
            max = head;
            max_sum = head->sum;
            max_idx = head->idx;
            while (runner != nullptr) {
                if (runner->sum > max_sum) {
                    max_sum = runner->sum;
                    max_idx = runner->idx;
                    max = runner;
                }
                runner = runner->next;
            }
            // cout<<"///////////////////"<<endl;
            // print();
            // cout<<"///////////////////"<<endl;
            return;
        }
        if (head == nullptr || number == 0) {
            Node* newNode = new Node(value);
            head = newNode;
            tail = newNode;
            max = newNode;
            newNode->next = nullptr;
            number = 1;
            return;
        }

        tail->next = new Node(value);
        if (value.sum > max_sum) {
            // this->max_sum = value.sum;
            // this->max = tail->next;
            max = tail->next;
            max_sum = value.sum;
            max_idx = value.idx;
        }
        tail = tail->next;
        tail->next = nullptr;
        number++;
        return;
    };
    void push_back(int sum, int index) {
        Node newNode(sum, index);
        push_back(newNode);
    }
    void push_front(Node value) {
        if (head == nullptr || number == 0) {
            Node* newNode = new Node(value);
            head = newNode;
            tail = newNode;
            number = 1;
            return;
        }
        Node* temp = head;
        Node* newNode = new Node(value);
        if (value.sum > this->max_sum) {
            this->max_sum = value.sum;
            this->max = newNode;
        }
        head = newNode;
        head->next = temp;
        number++;
        return;
    };
    per_for_knn() {
        head = nullptr;
        tail = nullptr;
        number = 0;
        max_number = 5;
    }
    per_for_knn(int a) {
        this->max_number = a;
    }
    per_for_knn(int a, int b) {
        Node in(a, b);
        push_back(in);
    }
    long long int return_max_sum() {
        if (number <= max_number) return 0;
        return max_sum;
    }

};


class kNN {
private:
    int k;
    Dataset* xtr;
    Dataset* ytr;
public:
    kNN(int k = 5) { if (k > 0)this->k = k; else this->k = 5; };
    void fit(const Dataset& X_train, const Dataset& y_train) {
        xtr = new Dataset(X_train);
        ytr = new Dataset(y_train);
        return;
    };
    Dataset predict(const Dataset& X_test) {
        //cout << k << endl;
        int t1, t2;
        X_test.getShape(t1, t2);// ex: 2 784
        // cout<<t1<<" "<<t2<<endl;

        int tt1, tt2;
        xtr->getShape(tt1, tt2);
        // cout<<tt1<<" "<<tt2<<endl;// ex: 1 784

        SList<SList<int>*>* temp_data = X_test.per_get_data_const();
        SList<SList<int>*>* temp_out = new SList<SList<int>*>;
        SList<SList<int>*>* temp_per_data = xtr->per_get_data();
        SList<SList<int>*>* temp_per_label = ytr->per_get_data();

        per_for_knn pkk(k);//pkk(k);
        // SList<per_for_knn>* ssl_knn;
        int ssl_knn_have_entered = 0;

        // for (int i=0;i<k;i++)ssl_knn->push_back(pkk);

        for (int i = 0; i < t1; i++) {
            //
            // long long int arr_sum[k];
            // int arr_idx[k];
            // for (int j = 0; j < k; j++) {
            //     arr_sum[j] = -1;
            //     arr_idx[j] = -1;
            // }


            //
            int out_idx = -1;
            long long int sum = 0;
            pkk.clear();
            // for (int j=0;j<t2;j++){
            //     int xt_data = temp_data->get(i)->get(j);
                // cout<<temp_data->get(i)->get(j)<<" ";

            for (int m = 0; m < tt1; m++) {
                long long int per_temp_sum = 0;
                // cout<<xtr_data<<" ";
                int j = 0;
                for (; j < t2; j++) {
                    if (per_temp_sum >= sum && sum != 0) break;
                    int xtr_data = temp_per_data->get(m)->get(j);
                    int xt_data = temp_data->get(i)->get(j);
                    per_temp_sum += (xtr_data - xt_data) * (xtr_data - xt_data);
                }
                if (j == t2) {
                    //cout << "per_temp_sum = " << per_temp_sum << "   temp_per_label->get(m)->get(0)) = " << temp_per_label->get(m)->get(0) << endl;
                    //cout<< per_temp_sum << "," << temp_per_label->get(m)->get(0) << endl;
                    pkk.push_back(per_temp_sum, temp_per_label->get(m)->get(0));
                    sum = pkk.return_max_sum();
                }
                /*
                per_temp_sum = 6636757   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 7899025   temp_per_label->get(m)->get(0)) = 0
per_temp_sum = 7260433   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 5919767   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 6635776   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 4297187   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 7274968   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 6365047   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 6717922   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5917904   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 6054829   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 6247051   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 5056434   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 6206366   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 5493659   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 5664547   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5147237   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 5628723   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 5460109   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 4996569   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 5035546   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 3658123   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 2958647   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 5341689   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 7552299   temp_per_label->get(m)->get(0)) = 0
per_temp_sum = 6354211   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 5069701   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4626472   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 6306785   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 3910354   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5938835   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3990952   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5539898   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 4406622   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 5213036   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 5142283   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 3587792   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4476323   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 4560014   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 4525379   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3947781   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 4251547   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 4086153   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4152639   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 3599822   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3250604   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3477950   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 3649097   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 3771918   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3596984   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 6615457   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 6710133   temp_per_label->get(m)->get(0)) = 0
per_temp_sum = 9102175   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 6500351   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 7674858   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 5852579   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 8128944   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4703993   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 6330640   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 5314444   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 6583865   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 2498795   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 6136838   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 5411947   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 5309151   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 4689490   temp ...snip... >get(0)) = 7
per_temp_sum = 6609546   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 7378851   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 6477898   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 6533000   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 6609180   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 6005762   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 6312254   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 6084557   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 6176285   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 6083839   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3769673   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 5337334   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 5959981   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 5809705   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 4945069   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 5163911   temp_per_label->get(m)->get(0)) = 7
per_temp_sum = 4831084   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 4427097   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 4590503   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 5439277   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 6764649   temp_per_label->get(m)->get(0)) = 0
per_temp_sum = 7273867   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 4228155   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5535656   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 5633485   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 4636752   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5607025   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3933304   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5071028   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 5322936   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 4955330   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 3733592   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 2334258   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 3688050   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3582905   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 2425305   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 3770231   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 3582222   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 3706314   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 2736342   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 3597869   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 2959152   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 2679829   temp_per_label->get(m)->get(0)) = 8
per_temp_sum = 6637933   temp_per_label->get(m)->get(0)) = 5
per_temp_sum = 9439567   temp_per_label->get(m)->get(0)) = 0
per_temp_sum = 6927417   temp_per_label->get(m)->get(0)) = 4
per_temp_sum = 6355939   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 7260772   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 8025489   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 5283620   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 7205363   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 5619828   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4756254   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3875845   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 5612824   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 5432327   temp_per_label->get(m)->get(0)) = 6
per_temp_sum = 5061627   temp_per_label->get(m)->get(0)) = 1
per_temp_sum = 4254336   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 4747882   temp_per_label->get(m)->get(0)) = 9
per_temp_sum = 4928331   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 4060559   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3284717   temp_per_label->get(m)->get(0)) = 2
per_temp_sum = 4172251   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 3987814   temp_per_label->get(m)->get(0)) = 3
per_temp_sum = 2832705   temp_per_label->get(m)->get(0)) = 3
                */
                //if (per_temp_sum < sum || sum == 0) { sum = per_temp_sum; out_idx = temp_per_label->get(m)->get(0); }// k=1
                //per_add_array(arr_idx, arr_sum, this->k, temp_per_label->get(m)->get(0), per_temp_sum);
            }
            out_idx = pkk.get_idx();
            //cout << out_idx << endl;
            SList<int>* temp_out_2 = new SList<int>;//
            temp_out_2->push_back(out_idx);
            temp_out->push_back(temp_out_2);

        }
        SList<string>* temp_out_label = ytr->per_get_label();
        Dataset* out = new Dataset(temp_out, temp_out_label, t1, 1);
        return *out;
    };
    double score(const Dataset& y_test, const Dataset& y_pred) {
        double out_count = 0;
        double out_correct = 0;
        int yt1, yt2;
        y_test.getShape(yt1, yt2);// ex: 2 784
        int yp1, yp2;
        y_pred.getShape(yp1, yp2);// ex: 2 784
        if (yp1 != yt1) return 0;
        // cout<<yt1<<" "<<yt2<<endl;
        SList<SList<int>*>* in = y_test.per_get_data_const();
        SList<SList<int>*>* out = y_pred.per_get_data_const();
        for (int i = 0; i < yt1; i++) {
            if (in->get(i)->get(0) == out->get(i)->get(0)) out_correct++;
            out_count++;
        }
        cout<< out_correct <<" "<< out_count<<endl;
        return (double)(out_correct / out_count);
    };
};

// Please add more or modify as needed