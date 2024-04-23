/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here
    if (s.empty()) {
      return 0;
    }
    T top_ = s.top();
    s.pop();
    T sum_ = top_ + sum(s); // Recursion call before push, Keeps original order of stack
    s.push(top_ );
    return sum_;


    // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
  stack<char> s;
  if (input.empty()) {
    return true;
  }

  for (unsigned i = 0; i < input.size(); i++) {
    char a = input.front();
    if (a == '[') {
      s.push(a);
    }
    if (a == ']') {
      if (!s.empty()) {
        s.pop();
      }
      else {
        return false;
      }
    }
    input.pop();
    input.push(a);
  }

  if (s.empty()) {
    return true;
  }

  return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // optional: queue<T> q2;

    // Your code here

    queue<T> q2;
    unsigned i = 1;
    while(!q.empty()) {

      if (i % 2 == 0) {
        if (i > q.size()) {
           i = q.size();
         }

         for (unsigned j = 0; j < i; j++) {
           T a = q.front();
           s.push(a);
           q.pop();
         }

         for (unsigned j = 0; j < i; j++) {
           T a = s.top();
           q2.push(a);
           s.pop();
         }
       }
       else {
         if (i > q.size()) {
           i = q.size();
         }
         for (unsigned j = 0; j < i; j++) {
           T a = q.front();
           q2.push(a);
           q.pop();
         }
       }
       i++;
     }
     q = q2;
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
  bool retval = false; // optional
  T queue_;
  T stack_;

  if (s.empty()) {
    return true;
  }

  stack_ = s.top();
  s.pop();
  retval = verifySame(s, q); //Getting to bottom of stack

  s.push(stack_);

  queue_ = q.front();
  q.pop();
  q.push(queue_);

  if (stack_ != queue_) {
    return false;
  }

  return retval;
}


}
