from django.shortcuts import render
from models import Dochody
from models import Wydatki
from django.views.generic import TemplateView
from django.views.generic import ListView
from django.views.generic import DetailView

from django.shortcuts import render
from django.shortcuts import render_to_response
from django.http import HttpResponseRedirect
from django.http import HttpResponse
from forms import *
from django.contrib import auth
from django.core.context_processors import csrf
import datetime
# Create your views here.

#logowanie
def login(request):
	c={}
	c.update(csrf(request))
	return render_to_response('login.html',c)
	
def auth_view(request):
	if request.method == "POST":
		username=request.POST.get('username','')
		password=request.POST.get('password','')
		user=auth.authenticate(username=username,password=password)
	
		if user is not None:
			auth.login(request,user)
			return HttpResponseRedirect('/loggedin/')
		else:
			return HttpResponseRedirect('/invalid/')
	return render(request, 'login.html')
		
def loggedin(request):
	return render_to_response('loggedin.html',{'full_name':request.user.username})
							 
def invalid_login(request):
	return render_to_response('invalid.html')
	
def logout(request):
	auth.logout(request)
	return render_to_response('logout.html')

def edycja(request):
	auth.logout(request)
	return render_to_response('edycja.html')

def edytowanie(request):
	auth.logout(request)
	return render_to_response('edytowanie.html')

def zestawienie(request):
	auth.logout(request)
	return render_to_response('zestawienie.html')

def dochody(request):
	auth.logout(request)
	return render_to_response('dochody.html')

def wydatki(request):
	auth.logout(request)
	return render_to_response('wydatki.html')
			
		
#do formatek		

def dochody(request):
	if request.user.is_authenticated():
		dct = {'lst': Dochody.objects.all()}
		return render(request, 'dochody.html',dct)
	
def formularzDoch(request):
	if request.user.is_authenticated():
		if request.method == 'POST':
			form = FormularzDoch(request.POST)	
			if form.is_valid():
				form.save(form.cleaned_data)
				return HttpResponseRedirect("zestawienie.html")	
		form = FormularzDoch()
		return render(request, 'dochody.html',{'form':form})
		
def wydatki(request):
	if request.user.is_authenticated():
		dct = {'lst': Wydatki.objects.all()}
		return render(request, 'wydatki.html',dct)
	
def formularzWyd(request):
	if request.user.is_authenticated():
		if request.method == 'POST':
			form = FormularzWyd(request.POST)	
			if form.is_valid():
				form.save(form.cleaned_data)
				return HttpResponseRedirect("zestawienie.html")	
		form = FormularzWyd()
		return render(request, 'wydatki.html',{'form2':form})
	
#do zestawienia
def Zestawka(request):
	if request.user.is_authenticated():
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'zestawienie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')
#do edycji

def EdytkaD(request):
	if request.user.is_authenticated():
		if request.method == "POST":
			idc=request.POST.get('name1','')
			instance1=Dochody.objects.get(tytul=idc)
			instance1.delete()
		return render(request, 'edycja.html')
	else:
		return render_to_response('baza.html')

def EdytkaW(request):
	if request.user.is_authenticated():
		if request.method == "POST":
			idc1=request.POST.get('ideczka2','')
			a1 = int('0' + idc1)
			instance2=Wydatki.objects.filter(id=a1)
			instance2.delete()
		return render(request, 'edycjaw.html')
	else:
		return render_to_response('baza.html')

def Edytor(request):
	if request.user.is_authenticated():
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'edytowanie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')

def Edit_doh(request):
	if request.user.is_authenticated():
		if request.method == 'POST':
			idx=request.POST.get('name1', '')
			index = int('0' + idx)
			query = Dochody.objects.get(id=index)
			return render(request, 'edit1.html',{'query': query})
	else:
		return render_to_response('baza.html')

def Edit_wyd(request):
	if request.method == 'POST':
		idx=request.POST.get('name1', '')
		index = int('0' + idx)
		query = Wydatki.objects.get(id=index)
		return render(request, 'edit2.html',{'query': query})

def Edyt_doh(request):
	if request.user.is_authenticated():
		if request.method == 'POST':
			idex=request.POST.get('id1', '')
			tytu=request.POST.get('tytul1', '')
			wart=request.POST.get('wartosc1', '')
			data=request.POST.get('data1', '')
			stal=request.POST.get('stalosc1', '')
			kate=request.POST.get('kategoria1', '')
			index = int('0' + idex)
			data2= datetime.datetime.strptime(data, "%Y-%m-%d")
			Dochody.objects.filter(id=index).update(tytul=tytu)
			Dochody.objects.filter(id=index).update(wartosc=wart)
			Dochody.objects.filter(id=index).update(data=data2)
			Dochody.objects.filter(id=index).update(stalosc=stal)
			Dochody.objects.filter(id=index).update(kategoria=kate)
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'edytowanie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')

def Edyt_wyd(request):
	if request.user.is_authenticated():
		if request.method == 'POST':
			idex=request.POST.get('id1', '')
			tytu=request.POST.get('tytul1', '')
			wart=request.POST.get('wartosc1', '')
			data=request.POST.get('data1', '')
			stal=request.POST.get('stalosc1', '')
			index = int('0' + idex)
			data2= datetime.datetime.strptime(data, "%Y-%m-%d")
			Wydatki.objects.filter(id=index).update(tytul=tytu)
			Wydatki.objects.filter(id=index).update(wartosc=wart)
			Wydatki.objects.filter(id=index).update(data=data2)
			Wydatki.objects.filter(id=index).update(stalosc=stal)
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'edytowanie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')

def del_doh(request):
	if request.user.is_authenticated():
		if request.method == "POST":
			idc=request.POST.get('obiekt1','')
			instance1=Dochody.objects.get(id=idc)
			instance1.delete()
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'edytowanie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')

def del_wyd(request):
	if request.user.is_authenticated():
		if request.method == "POST":
			idc=request.POST.get('obiekt1','')
			instance1=Wydatki.objects.get(id=idc)
			instance1.delete()
		query2 = Wydatki.objects.all()
		query= Dochody.objects.all()
		return render(request, 'edytowanie.html',{'query2': query2, 'query': query})
	else:
		return render_to_response('baza.html')

def baza(request):
	if request.user.is_authenticated():
		auth.logout(request)
		return render_to_response('baza.html')
	else:
		return render_to_response('baza.html')


