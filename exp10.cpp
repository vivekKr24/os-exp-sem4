#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <string>
#include <functional>
#include <utility>
#include <limits.h>

#define op(x) cout << x << endl; 
#define opp(x, y) cout << x << '\t' << y << endl; 
#define br cout << "---------------------------------------------" << endl; 

using namespace std; 

void warn(string msg) {
    cout << "WARNING ::: " << msg << endl; 
}
bool _lesser_(int a, int b) {
    return a < b; 
}
bool _greater_(int a, int b) {
    return a > b; 
}

class Process {
    private : 
        string p_name="null"; 
        int b_ad=-1; 
        int t_ad=-1;

    public :
        Process(string p_name="null", int b_ad=-1, int t_ad=-1) {
            this->p_name = p_name; 
            this->b_ad = b_ad; 
            this->t_ad = t_ad; 
        }

        // utilities 
        void print() {
            opp("process name\t", this->p_name); 
            opp("beginning_address", this->b_ad); 
            opp("terminating_address", this->t_ad); 
        }

        // beginning address 
        void resetBeginAddress(int val) {
            this->b_ad = val; 
        }
        int getBeginAddress() {
            return this->b_ad; 
        }

        // terminating address 
        void resetTermAddress(int val) {
            this->t_ad = val; 
        }
        int getTermAddress(){
            return this->t_ad; 
        }

        // name -- read only 
        string processName() {
            return (this->p_name); 
        }

        // operator overload 
        const bool operator<(const Process&chk)const {
            Process cpy = chk; 
            return ((this->b_ad) < (cpy.getBeginAddress())); 
		}
}; 

class Manage {
    private : 
        // object states 
        int TOTAL_MEMORY_CAPACITY; 
        bool * buffer; 
        set<Process> Record; 

        // utilities 
        void initWithZero() {
            for(int i = 0; i < (this->TOTAL_MEMORY_CAPACITY); ++i) 
                buffer[i] = 0; 
        }
        void resetBetween(int i, int j) {
            while(i < j) {
                buffer[i] = !buffer[i]; 
                ++i; 
            } 
        }
        bool isPresent(string check) {
            /*is the process present in the Record*/
            for(auto process : Record) 
                if(process.processName() == check) return true; 
            return false; 
        }
        void deleteProcess(Process p) {
            auto found = Record.find(p); 
            if(found != Record.end()) 
                Record.erase(found); 
        }

        // algorithms 
        /*bool represents status of the operation*/
        bool firstFit(Process&target, int size) {
            int i = 0, n = this->TOTAL_MEMORY_CAPACITY; 
            int j = 0; 
            /*allocate the first hole to the process*/
            while(j < n) {
                if(buffer[i] != buffer[j]) {
                    i = j; 
                }
                else ++j; 
                if(buffer[i] != 1) {
                    if(j - i >= size) {
                        target.resetBeginAddress(i); 
                        target.resetTermAddress(i+size - 1);
                        return true;  
                    }
                }
            }
            return false; 
        }

        bool bestFit(Process&target, int size) {
            int i = 0, n = this->TOTAL_MEMORY_CAPACITY; 
            int j = 0; 
            int I = -1, J = -2; 
            /*allocate the lower_bound of the spaces*/
            while(j < n) {
                if(buffer[i] == buffer[j]) {
                    ++j; 
                } else {
                    if(buffer[i] == 0) {
                        if(j-i >= size && j-i > J-I+1) {
                            J = j-1; 
                            I = i; 
                        }
                    }
                    i = j; 
                } 
            }
            if(buffer[i] == 0) {
                if(j-i >= size && j-i > J-I+1) {
                    J = j-1; 
                    I = i; 
                }
            }
            if(I == -1) return false; 
            target.resetBeginAddress(I); 
            target.resetTermAddress(I+size-1); 
            return true; 
        }
        bool worstFit(Process&target, int size) {
            int i = 0, n = this->TOTAL_MEMORY_CAPACITY; 
            int j = 0; 
            int I = 30, J = INT_MAX; 
            /*allocate the lower_bound of the spaces*/
            while(j < n) {
                if(buffer[i] == buffer[j]) {
                    ++j; 
                } else if(buffer[i] != buffer[j] || j == n) {
                    if(buffer[i] == 0) {
                        if(j-i >= size && j-i < J-I+1) {
                            J = j-1; 
                            I = i; 
                        }
                    }
                    i = j; 
                } 
            }
            if(buffer[i] == 0) {
                if(j-i >= size && j-i < J-I+1) {
                    J = j-1; 
                    I = i; 
                }
            }
            if(J == INT_MAX) return false; 
            target.resetBeginAddress(I); 
            target.resetTermAddress(I+size-1); 
            return true; 
        }
    public : 
        Manage(int TOTAL_MEMORY_CAPACITY) {
            this->TOTAL_MEMORY_CAPACITY = TOTAL_MEMORY_CAPACITY; 
            op("ALLOCATING GIVEN MEMORY"); 
            try {
                buffer = (bool *) malloc(sizeof(bool)*(this->TOTAL_MEMORY_CAPACITY)); 
                this->initWithZero(); 
                op("MEMORY_INITIALIZATION_SUCCESSFUL"); 
            } catch(...) {
                op("PROGRAM_CRASHED"); 
            }
            br; 
        }
        void allocate(string processName, int size, string type) {
            br; 
            if(this->isPresent(processName)) {
                warn("PROCESS WITH THE FOLLOWING NAME IS ALREADY PRESENT"); 
                return; 
            } else {
                bool isSuccess = false; 
                Process newProcess(processName); 
                if(type == "F") {
                    isSuccess = this->firstFit(newProcess, size); 
                } else if(type == "B") {
                    isSuccess = this->bestFit(newProcess, size); 
                } else {
                    isSuccess = this->worstFit(newProcess, size); 
                }
                if(isSuccess) {
                    this->resetBetween(newProcess.getBeginAddress(), newProcess.getTermAddress() + 1); 
                    (this->Record).insert(newProcess); 
                    op("PROCESS ALLOCATED SPACE"); 
                    newProcess.print(); 
                }
                else 
                    op("ERR ::: CANNOT_ALLOCATE_MEMORY DUE TO INSUFFICIENT SPACE"); 
            }
            br; 
        }
        void deAllocate(string processName) {
            br; 
            if((this->Record).empty()) {
                op("NOTHING TO DEALLOCATE");
                return; 
            }
            if(this->isPresent(processName)) {
                auto it = (this->Record).begin(); 
                auto loc = (this->Record).end();
                for(; it!=(this->Record).end(); ++it) {
                    Process cpy = (*it); 
                    if(cpy.processName() == processName) {
                        loc = it; 
                        break; 
                    }
                }
                Process toDelete = (*loc); 
                this->resetBetween(toDelete.getBeginAddress(), toDelete.getTermAddress() + 1); 
                (this->Record).erase(loc); 
                opp("DELETING ", processName); 
                toDelete.print(); 
                op("PROCESS DELETED SUCCESSFULLY")
            } else {
                string errMsg = processName + " IS NOT PRESENT\nTRY AGAIN"; 
                warn(errMsg); 
            }
            br; 
        }
        void compat() {
            br; 
            if((this->Record).empty()) {
                op("NO PROCESS IN MEMORY"); 
                br; 
                return; 
            } 
            auto f = [=](Process &a, int start) {
                int sz = a.getTermAddress() - a.getBeginAddress() + 1; 
                a.resetBeginAddress(start); 
                a.resetTermAddress(start + sz - 1); 
            }; 
            // compating algo 
            // collect all in vec and empty set 
            // make them conti 
            // init with 0 
            // from 0 to last set 1 
            vector<Process> temp; 
            while(!(this->Record).empty()) {
                temp.push_back( *((this->Record).begin()) ); 
                (this->Record).erase((this->Record).begin()); 
            }

            f(temp[0], 0); 

            for(int i = 1; i < temp.size(); ++i) {
                f(temp[i], temp[i-1].getTermAddress() + 1); 
            }
            this->initWithZero(); 
            
            for(int i = 0; i < temp.back().getTermAddress() + 1; ++i) {
                (this->buffer)[i] = 1; 
            }

            for(auto p : temp) {
                (this->Record).insert(p); 
            }
            op("COMPACTING_SUCCESSFUL DISPLAYING STAT"); 
            this->stat(); 
        }
        void stat() {
            br; 
            for(auto process : (this->Record)) 
                process.print(); 
            op("\n"); 
            int i = 0, n = this->TOTAL_MEMORY_CAPACITY; 
            int j = 0; 
            /*allocate the lower_bound of the spaces*/
            while(j < n) {
                if(buffer[i] == buffer[j]) {
                    ++j; 
                } else if(buffer[i] != buffer[j]) {
                    if(buffer[i] == 0) {
                        cout << "UNALLOCATED_BETWEEN " << " [" << i << ", " << j-1 << "]" << endl; 
                    }
                    i = j; 
                } 
            }
            if(buffer[i] == 0) {
                cout << "UNALLOCATED_BETWEEN " << " [" << i << ", " << j-1 << "]" << endl; 
            }
            br; 
        }
};



int main() {
    string OPERATION_TYPE; 
    Manage R(2000); 
    while(1) {
        cout << "allocator> ";
        cin >> OPERATION_TYPE; 
        if(OPERATION_TYPE == "RQ") {
            string pname; cin >> pname; 
            int size; cin >> size; 
            string strat; cin >> strat; 

            R.allocate(pname, size, strat); 
        } else if(OPERATION_TYPE == "RL") {
            string pname; cin >> pname; 

            R.deAllocate(pname); 
        } else if(OPERATION_TYPE == "C") {

            R.compat(); 
        } else if(OPERATION_TYPE == "STAT") {

            R.stat(); 
        } else if(OPERATION_TYPE == "X") {
            break; 
        } else {
            warn("COMMAND INVALID"); 
        }
    }
    return 0; 
}