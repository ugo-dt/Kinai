#!python3

import json, os, sys
from pathlib import Path

from Kinako import KnClass, KnGenerator, KINAI_TYPES, KINAI_IGNORED_TYPES, KnNamespace

def main(json_dir: Path, header_output_path: Path, source_output_path: Path):
	with open(Path(json_dir, 'namespaceKinai.json')) as kinai:
		json_data = json.load(kinai)
		for i in range(0, len(json_data['doxygen']['compounddef']['innerclass'])):
			__data = json_data['doxygen']['compounddef']['innerclass'][i]

			__type: str = __data['#text'].replace('Kinai::', '')
			if __type in KINAI_IGNORED_TYPES:
				continue
			KINAI_TYPES.add(__type)

	with open(Path(header_output_path), 'w') as header_file, open(Path(source_output_path), 'w') as source_file:
		header = KnGenerator(json_dir, header_file)
		source = KnGenerator(json_dir, source_file)

		header.write_from_file(Path(f'{os.path.dirname(__file__)}/output/kinako_template.h'))
		header.writeline('')

		for t in sorted(KINAI_TYPES):
			header.writeline(f'typedef struct Kn{t} Kn{t};')
		header.writeline('')

		with open(Path(json_dir, 'index.json')) as kinai:
			index = json.load(kinai)
			data: list[dict] = index['doxygenindex']['compound']
			
			namespaces: list[KnNamespace] = []
			classes: list[KnClass] = []

			for item in data:
				match item['@kind']:
					case 'namespace':
						namespaces.append(KnNamespace(item))
					case 'class' | 'struct':
						classes.append(KnClass(item))
					case _:
						pass

			for n in namespaces:
				header.writeline(n.__c__())
			
			source.writeline('#include "kinako.h"\n#include <Kinai/Kinai.hpp>\n')
			for c in classes:
				header.writeline(c.__c__())
				source.writeline(c.__cpp__())
			
if __name__ == '__main__':
	json_dir = f'{os.path.dirname(__file__)}/output/json'
	if len(sys.argv) == 2:
		json_dir = sys.argv[1]

	main(
		json_dir=Path(json_dir),
		header_output_path=Path(f'{os.path.dirname(__file__)}/output/kinako.h'),
		source_output_path=Path(f'{os.path.dirname(__file__)}/output/kinako.cpp')
	)
