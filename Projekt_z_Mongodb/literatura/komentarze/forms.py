from django import forms
from models import Dochody
from models import Wydatki

class FormularzDoch(forms.ModelForm):
	class Meta:
		model=Dochody
	
class FormularzWyd(forms.ModelForm):
	class Meta:
		model=Wydatki

class IdForm(forms.Form):
	Id = forms.CharField(label='Tytul', max_length=30)	
#class FormularzArt(forms.Form):
	#pass
