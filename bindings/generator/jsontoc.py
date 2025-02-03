import json, sys, os
from pathlib import Path
from typing import Literal

KINAI_TYPES: set[str] = set()
IGNORED_TYPES = ['TokenBase', 'Parser', 'is_token_type']

class KinakoFunction:
	def __init__(self, definition: str, argsstring: str, __compoundname: str, __isstatic: Literal['yes', 'no']):
		self.name: str = 'unnamed_function'
		self.args: list[str] = []
		self.static: bool = False
		self.ret: str = ''
		self.retref: bool = False

		self.find_name_and_return_type(definition)
		self.find_arguments(definition, argsstring, __compoundname, __isstatic)
	
	def __str__(self):
		return f'{self.ret} {self.name}({', '.join(self.args) if len(self.args) > 1 else self.args[0]});{' // [retref]' if self.retref else ''}'

	def find_name_and_return_type(self, definition: str):
		words = [word.strip() for word in definition.partition('Kinai::')]

		for i in range(0, len(words)):
			words[i] = words[i].replace('static', '')
			words[i] = words[i].replace('virtual', '')
		
		i: int = 0
		while i < len(words):
			if words[i] == 'Kinai::':
				break
			if words[i] == 'virtual':
				i += 1
				continue

			# Kinai types
			words[i] = f' {words[i]} '
			for __t in sorted(KINAI_TYPES):
				if f' {__t} ' in words[i]:
					words[i] = words[i].replace(__t, f'Kn{__t}')
			
			# Ref, Scope
			for ptr in ['Ref', 'Scope', 'std::vector']:
				if f'{ptr}< ' in words[i]:
					words[i] = words[i].replace(f'{ptr}< ', '')
					if words[i].endswith('&') or words[i].endswith('*'):
						words[i] = words[i].replace(' > ', '')
						words[i] = words[i].replace('*> ', '')
					else:
						words[i] = words[i].replace(' > ', '*')
						words[i] = words[i].replace('*> ', '*')
			
			self.ret += words[i].strip()
			i += 1

		if self.ret:
			self.ret = self.ret.replace('std::string', 'const char*')
			if '&' in self.ret:
				self.retref = True
				self.ret = self.ret.replace('&', '*').replace(' *', '*')
		else:
			self.ret = 'void'

		i += 1
		self.name = 'Kn' + words[i]	\
			.replace('::', '_')		\
			.replace('~', 'Destroy')

	def find_arguments(self, definition: str, argsstring: str, __compoundname: str, __isstatic: Literal['yes', 'no']):
		__defwords = definition.split('::')
		constructor: bool = __defwords[-1] == __defwords[-2]

		static: bool = True if __isstatic == 'yes' else False
		argslist: list[str] = [arg.strip() for arg in argsstring.replace('(', '', 1).replace(')', '', 1).split(',')]
		compoundname = __compoundname.replace('Kinai::', 'Kn').replace('::', '_')
		const_self: bool = False

		print(argslist)
		for arg in argslist:
			if arg.startswith('const'):
				const_self = True
				arg = arg.removeprefix('const').strip()
			if arg == '=default' or arg == 'override':
				continue
			self.args.append(arg.replace('&', '*').replace('std::string', 'char').removesuffix('=0'))

		if constructor:
			self.ret = f'{compoundname}*'
		elif not static:
			if const_self:
				compoundname = 'const ' + compoundname
			self.args.insert(0, (f'{compoundname}* self'))

		if self.args:
			self.args = [arg for arg in self.args if arg]
		if not self.args:
			self.args.append('void')
		
def main(__dirpath: str):
	output_path = f'{os.path.dirname(__file__)}/../kinako.h'

	with open(Path(output_path), 'a') as output_file:
		functions: list[KinakoFunction] = []
		output_file.truncate(0)

		with open(f'{os.path.dirname(__file__)}/kinako_template.h') as template:
			output_file.write(template.read())

		# __path = 'classKinai_1_1OrthographicCameraController.json'
		for __path in sorted(os.listdir(__dirpath)):
			if not __path.endswith('.json'):
				continue
			if not __path.startswith('class') and not __path.startswith('struct'):
				continue

			with open(Path(__dirpath, __path)) as file:
				json_data = json.load(file)
				__compoundname: str = json_data['doxygen']['compounddef']['compoundname']
				compoundname = __compoundname.replace('Kinai::', 'Kn').replace('::', '_')

				if not compoundname.removeprefix('Kn') in IGNORED_TYPES:
					output_file.write(f'typedef struct {compoundname} {compoundname};\n')
				try:
					for i in range(0, len(json_data['doxygen']['compounddef']['sectiondef'])):
						data: dict = json_data['doxygen']['compounddef']['sectiondef'][i]

						functions_keys: list[str] = ['public-func', 'public-static-func']
						for key in functions_keys:
							if data['@kind'] == key:
								if type(data['memberdef']) is list:
									for member in data['memberdef']:
										functions.append(KinakoFunction(member['definition'], member['argsstring'], compoundname, member['@static']))
								elif type(data['memberdef']) is dict:
									functions.append(KinakoFunction(data['memberdef']['definition'], data['memberdef']['argsstring'], compoundname, data['memberdef']['@static']))
				except:
					pass
					# print(f'Wrote {file.name} to {output_path}')
	
		output_file.write('\n')
		for f in functions:
			if not f.name.startswith('KnParser') and not '_EVENT_CLASS_' in f.name and not f.ret.endswith('iterator') and f.ret != 'sg_environment' and f.ret != 'sg_swapchain' and not f.ret.startswith('Statistics'):
				output_file.write(f'KINAKO_API {str(f)}\n')

if __name__ ==  '__main__':
	json_dir = f'{os.path.dirname(__file__)}/json'
	if len(sys.argv) == 2:
		json_dir = sys.argv[1]

	with open(Path(json_dir, 'namespaceKinai.json')) as kinai:
		json_data = json.load(kinai)
		for i in range(0, len(json_data['doxygen']['compounddef']['innerclass'])):
			data = json_data['doxygen']['compounddef']['innerclass'][i]

			__type: str = data['#text'].replace('Kinai::', '')
			if __type in IGNORED_TYPES:
				continue
			KINAI_TYPES.add(__type)

	KINAI_TYPES.add('KeyCode')
	KINAI_TYPES.add('MouseButton')

	main(json_dir)
