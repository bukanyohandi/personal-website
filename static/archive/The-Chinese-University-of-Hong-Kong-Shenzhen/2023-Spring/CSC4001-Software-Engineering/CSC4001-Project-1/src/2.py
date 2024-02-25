import ast

class UndefinedVariablesFunction(ast.NodeVisitor):
    def __init__(self, func_id, defined_variables, tree, validator, call_obj):
        self.func_id = func_id
        self.defined_variables = set().union(defined_variables)
        self.tree = tree
        self.validator = list() + validator
        self.call_obj = call_obj
        self.stop_call = False
        self.from_fdef = False
        self.name_count = 0
        self.defined_var_for = set()
        self.undefined_variable_usages = 0
    
    def visit_FunctionDef(self, node):
        if node.name != self.func_id or self.stop_call:
            return

        global defined_var_for

        self.defined_var_for = defined_var_for[node]

        self.undefined_variable_usages = 0

        not_allowed = set()

        cnt = 0
        for default in node.args.defaults:
            if isinstance(default, ast.Constant):
                cnt += 1
            elif isinstance(default, ast.BinOp) or isinstance(default, ast.Compare):
                self.from_fdef = True

                self.visit(default)

                if self.name_count > 0:
                    not_allowed.add(cnt)

                self.from_fdef = False
                self.name_count = 0
                cnt += 1

        sz = 0
        for arg in node.args.args:
            sz += 1
        idx = 0

        for arg in node.args.args:
            if (idx < len(self.validator) and self.validator[idx]) or (idx >= sz - cnt and (idx - sz + cnt not in not_allowed)):
                self.defined_variables.add(arg.arg)
            else:
                try:
                    self.defined_variables.remove(arg.arg)
                except:
                    pass

            idx += 1

        analyzer = UndefinedVariablesAnalyzer(self.tree, self.defined_variables)
        analyzer.generic_visit(node)

        self.undefined_variable_usages += analyzer.undefined_variable_usages

    def visit_Call(self, node):
        if node == self.call_obj:
            self.stop_call = True

    def visit_Name(self, node):
        if self.from_fdef and isinstance(node.ctx, ast.Load) and node.id not in self.defined_var_for:
            self.name_count += 1
    
class UndefinedVariablesAnalyzer(ast.NodeVisitor):
    def __init__(self, tree, defined_variables):
        self.tree = tree
        self.defined_variables = set().union(defined_variables)
        self.undefined_variable_usages = 0
        self.from_assign = False
        self.last_assigned_variables = list()
        self.pending_update = list()
        
    def visit_FunctionDef(self, node):
        global defined_var_for, taken

        if node not in taken:
            defined_var_for[node] = set()
            for var in self.defined_variables:
                defined_var_for[node].add(var)

        taken.add(node)

        return

    def visit_Call(self, node):
        if not isinstance(node.func, ast.Name):
            return

        validator = []
        for arg in node.args:
            if isinstance(arg, ast.Name):
                validator.append(bool(arg.id in self.defined_variables))
            elif isinstance(arg, ast.Constant):
                validator.append(True)
            elif isinstance(arg, ast.BinOp) or isinstance(ast.Compare):
                self.previous_undefined_variable_usages = self.undefined_variable_usages
                self.from_assign = True
                self.visit(arg)
                self.from_assign = False
                validator.append(bool(self.previous_undefined_variable_usages == self.undefined_variable_usages))
                self.undefined_variable_usages = self.previous_undefined_variable_usages
        
        args = set()
        for arg in node.keywords:
            self.previous_undefined_variable_usages = self.undefined_variable_usages
            self.from_assign = True
            self.visit(arg)
            self.from_assign = False
            if self.previous_undefined_variable_usages == self.undefined_variable_usages:
                args.add(arg.arg)
            self.undefined_variable_usages = self.previous_undefined_variable_usages

        f = UndefinedVariablesFunction(node.func.id, self.defined_variables.union(args), self.tree, validator, node)
        f.visit(self.tree)

        self.undefined_variable_usages += f.undefined_variable_usages

    def visit_Assign(self, node):

        self.previous_undefined_variable_usages = self.undefined_variable_usages

        for target in node.targets:
            if isinstance(target, ast.Name):
                self.last_assigned_variables.append(target.id)
            elif isinstance(target, ast.Tuple) and len(self.last_assigned_variables) == 0:
                for var in target.elts:
                    self.last_assigned_variables.append(var.id)
                break

        if isinstance(node.value, ast.Tuple):
            for var in node.value.elts:
                if isinstance(var, ast.Constant):
                    self.pending_update.append(True)
                else:
                    self.from_assign = True
                    self.visit(var)
                    self.from_assign = False
                    self.pending_update.append(bool(self.previous_undefined_variable_usages == self.undefined_variable_usages))
                    self.previous_undefined_variable_usages = self.undefined_variable_usages
        else:
            self.from_assign = True
            self.visit(node.value)
            self.from_assign = False
            self.pending_update.append(bool(self.previous_undefined_variable_usages == self.undefined_variable_usages))

        if len(self.pending_update) != len(self.last_assigned_variables):
            return
        
        for i in range(len(self.pending_update)):
            if self.pending_update[i]:
                self.defined_variables.add(self.last_assigned_variables[i])
            else:
                try:
                    self.defined_variables.remove(self.last_assigned_variables[i])
                except:
                    pass

        self.last_assigned_variables = list()
        self.pending_update = list()

        return self.previous_undefined_variable_usages == self.undefined_variable_usages

    def visit_Name(self, node):
        if self.from_assign and isinstance(node.ctx, ast.Load) and node.id not in self.defined_variables:
            self.undefined_variable_usages += 1

def count_undefined_variable_usages(code):
    global defined_var_for, taken
    defined_var_for = dict()
    taken = set()

    tree = ast.parse(code)
    analyzer = UndefinedVariablesAnalyzer(tree, set())
    analyzer.visit(tree)
    return analyzer.undefined_variable_usages

if __name__ == "__main__":
    # code_snippet = "\n".join(input().split("\\n"))

    # Below code_snippet supports comments removal
    lines = input().split("\\n")

    uncommented_lines = []
    for line in lines:
        uncommented_lines.append(line.split("#")[0])

    code_snippet = "\n".join(uncommented_lines)

    print(count_undefined_variable_usages(code_snippet))
