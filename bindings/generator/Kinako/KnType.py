KINAI_TYPES: set[str] = set()
KINAI_IGNORED_TYPES = ['TokenBase', 'Parser', 'is_token_type']

class KnType:
	def __init__(self, _type: str | dict):
		self.const: bool = False
		self.compound: bool = isinstance(_type, dict)
		self.type: str | dict = _type

		if self.compound:
			self.text: str | None = _type.get('#text') # type: ignore
			if self.text is not None:
				self.const = self.text.strip().startswith('const')

			ref: dict = _type.get('ref', {}) # type: ignore
			self.ref_text = ref.get('#text', '')
			self.__kindref: str = ref.get('@kindref', '')
			self.__refid: str = ref.get('@refid', '')
			
	def __c__(self) -> str:
		if self.compound:
			return f'{'const ' if self.const else ''}Kn{self.ref_text}*'
		else:
			if self.type is None:
				return 'void'

			__type: str = self.type.strip() # type: ignore

			# c++ std types
			if 'std::' in __type or '<' in __type or '>' in __type:
				return 'void*'

			words = __type.split(' ')
			i = 0
			while i < len(words):
				words[i] = words[i].replace('&', '*')

				# GLM types
				if 'glm::' in words[i]:
					words[i] = words[i].replace('quat', 'versor')
					words[i] = f'{words[i].replace('glm::', '')}s'

				# Kinai types
				if words[i] in KINAI_TYPES:
					words[i] = f'Kn{words[i]}'
				opaque_types = ['string_type', 'iterator', 'const_iterator', 'iterator_type']
				if words[i] in opaque_types:
					words[i] = 'void*'

				if words[i] == 'constexpr':
					words.pop(i)
				i += 1
			
			__type = ' '.join(words)

			# Formatting
			__type = __type.replace(' *', '*')

			return f'{__type}'
