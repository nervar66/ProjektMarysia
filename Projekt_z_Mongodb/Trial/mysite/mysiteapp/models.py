from django.db import models
#from mongoengine import *

# Create your models here.

class Dochody(models.Model):
	tytul     = models.CharField(max_length=30)
	wartosc   = models.IntegerField()
	data      =	models.DateField()
	stalosc   = models.IntegerField()
	kategoria = models.CharField(max_length=30)
class Wydatki(models.Model):
	tytul     = models.CharField(max_length=30)
	wartosc   = models.IntegerField()
	data      =	models.DateField()
	stalosc   = models.IntegerField()




#class Dochody(Document):
#	tytul     = StringField(max_length=30)
#	wartosc   = IntField()
#	data      = DateTimeField()
#	stalosc   = IntField()
#	kategoria = StringField(max_length=30)
#class Wydatki(Document):
#	tytul     = StringField(max_length=30)
#	wartosc   = IntField()
#	data      = DateTimeField()
#	stalosc   = IntField()
