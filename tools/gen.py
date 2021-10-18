import os
import sys

def parse_array_name(name):
    dim = []
    pos = name.find('[')
    if '[' in name:
        s0, s1 = name[:pos], name[pos:]
        dim = s1.replace('[', '').split(']')
        dim = [int(s, 10) for s in dim if s != '']
        return s0, dim
    else:
        return name, dim

def get_type_name(line):
    line = line.replace('\t', '    ')
    var_type, var_name, dim =  None, None, []
    if '*' in line:
        s0, s1 = line.split('*')
        var_type = 'c_void_p'
        var_name = s1.strip().split(';')[0]
    elif 'unsigned int' in line:
        var_type = 'c_uint32'
        var_name = line.split('unsigned int ')[1].split(';')[0]
    elif 'uint64_t' in line:
        var_type = 'c_uint64'
        var_name = line.split('uint64_t ')[1].split(';')[0]
    elif 'uint32_t' in line:
        var_type = 'c_uint32'
        var_name = line.split('uint32_t ')[1].split(';')[0]
    elif 'uint16_t' in line:
        var_type = 'c_uint16'
        var_name = line.split('uint16_t ')[1].split(';')[0]
    elif 'uint8_t' in line:
        var_type = 'c_uint8'
        var_name = line.split('uint8_t ')[1].split(';')[0]
    elif 'int64_t' in line:
        var_type = 'c_int64'
        var_name = line.split('int64_t ')[1].split(';')[0]
    elif 'int32_t' in line:
        var_type = 'c_int32'
        var_name = line.split('int32_t ')[1].split(';')[0]
    elif 'int16_t' in line:
        var_type = 'c_int16'
        var_name = line.split('int16_t ')[1].split(';')[0]
    elif 'int8_t' in line:
        var_type = 'c_int8'
        var_name = line.split('int8_t ')[1].split(';')[0]
    elif 'size_t' in line:
        var_type = 'c_uint64'
        var_name = line.split('size_t ')[1].split(';')[0]
    elif 'bool' in line:
        var_type = 'c_bool'
        var_name = line.split('bool ')[1].split(';')[0]
    elif 'int' in line:
        var_type = 'c_int32'
        var_name = line.split('int ')[1].split(';')[0]
    else:
        return None, None, []
    var_name, dim = parse_array_name(var_name.strip())
    return var_type, var_name, dim

def find_struct(header_file):
    with open(header_file, 'rt') as f:
        contents = f.readlines()
        i = 0
        while i < len(contents):
            line = contents[i]
            if 'typedef struct' in line:
                j = 1
                name = line.split('typedef struct')[1].strip()[1:]
                struct_dict[name] = []
                while not contents[i+j].strip().startswith('}'):
                    j += 1
                    line = contents[i+j].strip()
                    if len(line) == 0 or line.startswith('//') or ('/*' in line and '*/' in line) or ('{' in line) or ('}' in line):
                        continue  
                    if line.find('//') != -1: # remove comments at end of field definition
                        line = line[:line.find('//')]             
                    struct_dict[name].append(line)
                i += j
            i += 1

def gen_ctypes(var_name, var_fileds):
    print('#'*8, var_name)
    ctypes_out.append('class %s(PStruct):' % var_name)
    ctypes_out.append('    _fields_ = [')
    for line in var_fileds:
        vtype, vname, dim = get_type_name(line)
        if vtype != None and vname != None:
            if len(dim) == 0:
                ctypes_out.append('        ("%s", %s),' % (vname, vtype))
            else:
                type_str = vtype
                for d in dim:
                    type_str = '(%s)*%d' % (type_str, d)
                ctypes_out.append('        ("%s", %s),' % (vname, type_str))
    ctypes_out.append('    ]\n')

def parse_and_gen(header_file):
    # find all cpp struct definitions in header file
    find_struct(header_file)

    # generate python ctypes from cpp struct
    for k, v in struct_dict.items():
        gen_ctypes(k, v)

    # write ctypes definition into .py file
    outfile = '%s.py' % os.path.basename(header_file).split('.')[0]
    with open(outfile, 'wt') as f:
        f.writelines('\n'.join(ctypes_out))

if __name__ == '__main__':
    struct_dict, ctypes_out = {}, ['from pstruct import *\n']

    header_file = 'VBParserDef.h'
    if len(sys.argv) > 1:
        header_file = sys.argv[1]

    print('start to process %s ...' % header_file)
    parse_and_gen(header_file)

print('done')