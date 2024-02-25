import ast

class NegateOperations(ast.NodeTransformer):
    binary_operations = {
        ast.Add: ast.Sub,
        ast.Sub: ast.Add,
        ast.Mult: ast.Div,
        ast.Div: ast.Mult,
    }

    comparison_operations = {
        ast.Eq: ast.NotEq,
        ast.NotEq: ast.Eq,
        ast.Lt: ast.GtE,
        ast.Gt: ast.LtE,
        ast.LtE: ast.Gt,
        ast.GtE: ast.Lt,
    }

    def visit_BinOp(self, node):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        node.op = self.binary_operations.get(type(node.op), type(node.op))()
        return node

    def visit_Compare(self, node):
        node.left = self.visit(node.left)
        node.comparators = [self.visit(comparator) for comparator in node.comparators]
        node.ops = [self.comparison_operations.get(type(op), type(op))() for op in node.ops]
        return node

class RemoveUnusedFunctions(ast.NodeTransformer):
    def __init__(self, used_functions):
        self.used_functions = used_functions

    def visit_FunctionDef(self, node):
        if node.name in self.used_functions:
            return node
        else:
            return None

class FunctionCallsCollector(ast.NodeVisitor):
    def __init__(self, target_function_name):
        self.target_function_name = target_function_name
        self.inside_target_function = False
        self.called_functions = set()

    def visit_FunctionDef(self, node):
        if node.name == self.target_function_name:
            self.inside_target_function = True
            self.generic_visit(node)
            self.inside_target_function = False
        else:
            self.generic_visit(node)

    def visit_Call(self, node):
        if self.inside_target_function and isinstance(node.func, ast.Name):
            self.called_functions.add(node.func.id)
        self.generic_visit(node)

class CollectFunctionUsage(ast.NodeVisitor):
    def __init__(self):
        self.defined_functions = set()
        self.called_functions = set()
        self.used_functions = set()

    def visit_FunctionDef(self, node):
        self.defined_functions.add(node.name)

    def visit_Call(self, node):
        if isinstance(node.func, ast.Name):
            self.called_functions.add(node.func.id)
        self.generic_visit(node)

    def get_used_functions(self):
        self.used_functions = self.called_functions.intersection(self.defined_functions)
        return self.used_functions

class GlobalVariableFinder(ast.NodeVisitor):
    def __init__(self):
        self.global_variables = set()
        self.inside_function = False

    def visit_Global(self, node):
        for name in node.names:
            self.global_variables.add(name)

    def visit_Assign(self, node):
        for target in node.targets:
            if isinstance(target, ast.Name) and not self.inside_function:
                self.global_variables.add(target.id)
            elif isinstance(target, ast.Tuple) and not self.inside_function:
                for var in target.elts:
                    self.global_variables.add(var.id)
        self.generic_visit(node)

    def visit_FunctionDef(self, node):
        self.inside_function = True
        self.generic_visit(node)
        self.inside_function = False

    def visit_AsyncFunctionDef(self, node):
        self.inside_function = True
        self.generic_visit(node)
        self.inside_function = False

    def visit_Lambda(self, node):
        self.inside_function = True
        self.generic_visit(node)
        self.inside_function = False

def transform_code(code):
    tree = ast.parse(code)

    # Collect used functions
    usage_collector = CollectFunctionUsage()
    usage_collector.visit(tree)
    used_functions = usage_collector.get_used_functions()

    current_size = 0
    while current_size != len(used_functions):
        current_size = len(used_functions)

        recursed_functions = set()
        for target_function_name in used_functions:
            collector = FunctionCallsCollector(target_function_name)
            collector.visit(tree)

            recursed_functions = recursed_functions.union(collector.called_functions)

        used_functions = used_functions.union(recursed_functions)

    # Negate operations
    tree = NegateOperations().visit(tree)

    # Remove unused functions
    tree = RemoveUnusedFunctions(used_functions).visit(tree)

    # Output the transformed code
    print(ast.unparse(tree))
    print()

    # Collect and print global variables
    finder = GlobalVariableFinder()
    finder.visit(tree)
    for var_name in finder.global_variables:
        print(f"print({var_name})")

if __name__ == "__main__":
    # code_snippet = "\n".join(input().split("\\n"))

    # Below code_snippet supports comments removal
    lines = input().split("\\n")

    uncommented_lines = []
    for line in lines:
        uncommented_lines.append(line.split("#")[0])

    code_snippet = "\n".join(uncommented_lines)

    transform_code(code_snippet)
