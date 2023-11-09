#include "TDataLoop.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset

char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
#ifdef __APPLE__
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext->__ss.__rip);
#else
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
#endif
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;
#ifdef __APPLE__
  ((ucontext_t*)context)->uc_mcontext->__ss.__rip += 2;  // skip the seg fault
#else
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] += 2;  // skip the seg fault
#endif
}

#define ASSERT(cond) if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  }
#endif

/**
 * \struct TDataLoopTest
 * \defgroup TDataLoopTest
 * \brief Test cases for the TDataLoop class
 */
struct TDataLoopTest {
  // aliases
  using CTDataLoop = TDataLoop<char>;
  using STDataLoop = TDataLoop<string>;
  
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    CTDataLoop *q = new CTDataLoop();
    // check if the structure is as expected
    ASSERT(q->start == nullptr);
    ASSERT(q->count == 0);
    delete q;

    STDataLoop *s = new STDataLoop();
    // check if the structure is as expected
    ASSERT(s->start == nullptr);
    ASSERT(s->count == 0);
    delete s;
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    CTDataLoop *q = new CTDataLoop('1');
    // check if the structure is as expected
    ASSERT(q->start != nullptr);
    ASSERT(q->start->next == q->start);
    ASSERT(q->start->prev == q->start);
    ASSERT(q->start->data == '1');
    ASSERT(q->count == 1);
    delete q;

    STDataLoop *s = new STDataLoop("10");
    // check if the structure is as expected
    ASSERT(s->start != nullptr);
    ASSERT(s->start->next == s->start);
    ASSERT(s->start->prev == s->start);
    ASSERT(s->start->data == "10");
    ASSERT(s->count == 1);
    delete s;
}
  
  /**
   * \brief A test function for operator+= using char
   */
  static void OperatorPlusGetsTestChar() {

    CTDataLoop *q = new CTDataLoop();

    *q += '1';        // test single use
    // check if the structure is as expected
    ASSERT(q->start != nullptr);
    ASSERT(q->start->next == q->start);
    ASSERT(q->start->prev == q->start);
    ASSERT(q->start->data == '1');
    ASSERT(q->count == 1);
   

    *q += '3';
    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == '1');  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == '3');
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == '3');

    *q += '2';  
    ASSERT(q->count == 3);

    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == '2');
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == '3');
    ASSERT(q->start->prev->prev->prev == q->start);

    CTDataLoop *r = new CTDataLoop();
    ((*r += '1') += '3') += '2';    // test chaining (function return)
    ASSERT(r->count == 3);
    ASSERT(r->start != nullptr);
    ASSERT(r->start->data == '1');
    ASSERT(r->start->next != nullptr);
    ASSERT(r->start->next->data == '3');
    ASSERT(r->start->prev != nullptr);
    ASSERT(r->start->prev->data == '2');
    ASSERT(r->start->next->next != nullptr);
    ASSERT(r->start->next->next->data == '2');
    ASSERT(r->start->next->next->next == r->start);
    ASSERT(r->start->prev->prev != nullptr);
    ASSERT(r->start->prev->prev->data == '3');
    ASSERT(r->start->prev->prev->prev == r->start);

    delete q;
    delete r;
  }

    /**
   * \brief A test function for operator+= using string
   */
  static void OperatorPlusGetsTestString() {

    STDataLoop *q = new STDataLoop();

    *q += "10";        // test single use
    // check if the structure is as expected
    ASSERT(q->start != nullptr);
    ASSERT(q->start->next == q->start);
    ASSERT(q->start->prev == q->start);
    ASSERT(q->start->data == "10");
    ASSERT(q->count == 1);
   

    *q += "30";
    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == "10");  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == "30");
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == "30");

    *q += "20";  
    ASSERT(q->count == 3);

    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == "20");
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == "30");
    ASSERT(q->start->prev->prev->prev == q->start);

    STDataLoop *r = new STDataLoop();
    ((*r += "10") += "30") += "20";    // test chaining (function return)
    ASSERT(r->count == 3);
    ASSERT(r->start != nullptr);
    ASSERT(r->start->data == "10");
    ASSERT(r->start->next != nullptr);
    ASSERT(r->start->next->data == "30");
    ASSERT(r->start->prev != nullptr);
    ASSERT(r->start->prev->data == "20");
    ASSERT(r->start->next->next != nullptr);
    ASSERT(r->start->next->next->data == "20");
    ASSERT(r->start->next->next->next == r->start);
    ASSERT(r->start->prev->prev != nullptr);
    ASSERT(r->start->prev->prev->data == "30");
    ASSERT(r->start->prev->prev->prev == r->start);

    delete q;
    delete r;
  }


  /**
   * \brief A test function for copy constructor using char
   */
  static void CopyConstructorTest() {
    CTDataLoop *r = new CTDataLoop('1');
    *r += '3';
    *r += '2';
    CTDataLoop *q = new CTDataLoop(*r);
    // check if the structure is as expected
    ASSERT(q->count == 3);

    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == '1');  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == '3');
    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == '2');
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == '2');
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == '3');
    ASSERT(q->start->prev->prev->prev == q->start);

    // check that updating r doesn't affect q
    *r += '5';
    ASSERT(r->count == 4);
    ASSERT(q->count == 3);
    ASSERT(r->start->prev->data == '5');
    ASSERT(q->start->prev->data == '2');

    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for assignment operator using string
   */
  static void OperatorAssignmentTest() {
    STDataLoop *r = new STDataLoop("10");
    *r += "30"; *r += "20";
    STDataLoop *q = new STDataLoop("15");
    *q = *r;
    // check if the structure is as expected
    ASSERT(q->count == 3);

    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == "10");  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == "30");
    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == "20");
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == "20");
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == "30");
    ASSERT(q->start->prev->prev->prev == q->start);

    // check that updating r doesn't affect q
    // TODO: add your own tests here

    delete r;
    delete q;
  }
  
  
  /**
   * \brief A test function for equality operator using char
   */
  static void OperatorEqualityTest() {
    CTDataLoop *q = new CTDataLoop();
    *q += '1'; *q += '3'; *q += '2';    
    CTDataLoop *r = new CTDataLoop();
    *r += '1'; *r += '3'; *r += '2';
    // check if they are the same
    ASSERT(*q == *r);

    q->start->data = '5';   // change node
    ASSERT(!(*q == *r));

    q->start->data = '1';   // reset to same
    q->start = q->start->next->next;   // move start
    ASSERT(!(*q == *r));

    q->start = q->start->prev->prev;  // reset to same
    *q += '8';               // add node
    ASSERT(!(*q == *r));
    
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for concatenate operator using string
   */
  static void OperatorConcatenateTest() {
    STDataLoop *q = new STDataLoop("10");
    *q += "30";
    STDataLoop *r = new STDataLoop("15");
    *r += "5";
    STDataLoop *s = new STDataLoop("100");
    *s = *q + *r;
    ASSERT(s->count == 4);

    // check if the structure is as expected
    ASSERT(s->start != nullptr);
    ASSERT(s->start->data == "10");
    ASSERT(s->start->next != nullptr);
    ASSERT(s->start->next->data == "30");
    ASSERT(s->start->next->next != nullptr);
    ASSERT(s->start->next->next->data == "15");
    ASSERT(s->start->next->next->next != nullptr);
    ASSERT(s->start->next->next->next->data == "5");
    ASSERT(s->start->next->next->next->next == s->start);

    // TODO: add prev tests

    // TODO: test that q and r have not changed

    delete s;
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for stream insertion operator using char
   */
  static void OperatorStreamInsertionTestChar() {
    CTDataLoop *q = new CTDataLoop();
    std::stringstream empty_ss;
    empty_ss << *q;
    ASSERT(empty_ss.str() == ">no values<");
    *q += 'A'; *q += 'B'; *q += 'C';
    std::stringstream ss;
    ss << *q;
    ASSERT(ss.str() == "-> A <--> B <--> C <-");
    delete q;
  }

  /**
   * \brief A test function for stream insertion operator using string
   */
  static void OperatorStreamInsertionTestString() {
    STDataLoop *q = new STDataLoop();
    std::stringstream empty_ss;
    empty_ss << *q;
    ASSERT(empty_ss.str() == ">no values<");
    *q += "10"; *q += "30"; *q += "20";
    std::stringstream ss;
    ss << *q;
    ASSERT(ss.str() == "-> 10 <--> 30 <--> 20 <-");
    delete q;
  }

  /**
   * \brief A test function for shift operator using char
   */
  static void OperatorShiftTest() {
    CTDataLoop *q = new CTDataLoop();
    for (char i = 'A'; i <= 'J'; i++) {
      *q += i;
    }
    *q ^ 0;
    ASSERT(q->start->data == 'A');
    *q ^ 1;
    ASSERT(q->start->data == 'B');
    *q ^ 5;
    ASSERT(q->start->data == 'G');
    *q ^ 20;
    ASSERT(q->start->data == 'G');
    *q ^ -1;
    ASSERT(q->start->data == 'F');
    *q ^ -8;
    ASSERT(q->start->data == 'H');
    *q ^ -49;
    ASSERT(q->start->data == 'I');
    
    delete q;
  }

  /**
   * \brief A test function for length function using string
   */
  static void FunctionLengthTest() {
    STDataLoop *q = new STDataLoop();
    ASSERT(q->length() == 0);
    *q += "10";
    ASSERT(q->length() == 1);
    *q += "30"; *q += "20";
    ASSERT(q->length() == 3);
    delete q;
  }

  /**
   * \brief A test function for splice function, depends on operator<< and operator+=
   */
  static void FunctionSpliceTest() {
    TDataLoop<int> *q = new TDataLoop<int>();
    for (int i = 1; i <= 4; i++) {
      *q += i;
    }
    TDataLoop<int> *r = new TDataLoop<int>();
    for (int j = 10; j <= 12; j++) {
      *r += j;
    }

    q->splice(*r, 0);
    ASSERT(q->count == 7);
    ASSERT(r->count == 0);
    ASSERT(r->start == nullptr);

    std::stringstream ss1;
    ss1 << *q;
    ASSERT(ss1.str() == "-> 10 <--> 11 <--> 12 <--> 1 <--> 2 <--> 3 <--> 4 <-");

    std::stringstream ss2;
    ss2 << *r;
    ASSERT(ss2.str() == ">no values<");
    
    TDataLoop<int> *p = new TDataLoop<int>();
    *p += 20;
    *p += 25;
    q->splice(*p, 9);
    ASSERT(q->count == 9);
    std::stringstream ss3;
    ss3 << *q;
    ASSERT(ss3.str() == "-> 10 <--> 11 <--> 20 <--> 25 <--> 12 <--> 1 <--> 2 <--> 3 <--> 4 <-");

    delete p;  // empty list 
    delete r;  // empty list
    delete q;  
  }

};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing TDataLoop" << endl;
  // register a seg fault handler
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  TDataLoopTest::DefaultConstructorTest();
  TDataLoopTest::NonDefaultConstructorTest();
  TDataLoopTest::OperatorPlusGetsTestChar();    // needed for below tests
  TDataLoopTest::OperatorPlusGetsTestString();    // needed for below tests

  TDataLoopTest::CopyConstructorTest();
  TDataLoopTest::OperatorAssignmentTest();
  TDataLoopTest::OperatorEqualityTest();
  TDataLoopTest::OperatorConcatenateTest();
  TDataLoopTest::OperatorStreamInsertionTestChar();
  TDataLoopTest::OperatorStreamInsertionTestString();

  TDataLoopTest::OperatorShiftTest();  // char
  TDataLoopTest::FunctionLengthTest();  // string
  TDataLoopTest::FunctionSpliceTest();   // int
  
  return 0;
}
