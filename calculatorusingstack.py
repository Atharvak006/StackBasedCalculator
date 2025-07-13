class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop() if not self.is_empty() else None

    def peek(self):
        return self.items[-1] if not self.is_empty() else None

    def is_empty(self):
        return len(self.items) == 0


def precedence(op):
    if op in ('+', '-'):
        return 1
    if op in ('*', '/'):
        return 2
    return 0


def apply_op(a, b, op):
    if op == '+':
        return a + b
    elif op == '-':
        return a - b
    elif op == '*':
        return a * b
    elif op == '/':
        return a // b  # Integer division like C
    return 0


def infix_to_postfix(expression):
    stack = Stack()
    postfix = []
    i = 0

    while i < len(expression):
        char = expression[i]

        if char.isdigit():
            # Handle multi-digit numbers
            num = []
            while i < len(expression) and expression[i].isdigit():
                num.append(expression[i])
                i += 1
            postfix.append(''.join(num))
            continue
        elif char == '(':
            stack.push(char)
        elif char == ')':
            while not stack.is_empty() and stack.peek() != '(':
                postfix.append(stack.pop())
            stack.pop()  # Pop '('
        elif char in "+-*/":
            while not stack.is_empty() and precedence(stack.peek()) >= precedence(char):
                postfix.append(stack.pop())
            stack.push(char)
        i += 1

    while not stack.is_empty():
        postfix.append(stack.pop())

    return postfix


def evaluate_postfix(postfix):
    stack = Stack()

    for token in postfix:
        if token.isdigit():
            stack.push(int(token))
        else:
            b = stack.pop()
            a = stack.pop()
            result = apply_op(a, b, token)
            stack.push(result)

    return stack.pop()


def main():
    infix = input("Enter infix expression: ").strip().replace(" ", "")
    postfix_list = infix_to_postfix(infix)
    print("Postfix expression:", ' '.join(postfix_list))
    result = evaluate_postfix(postfix_list)
    print("Result:", result)


if __name__ == "__main__":
    main()
