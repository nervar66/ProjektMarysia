from django.db import models
from mongoengine import *

# Create your models here.

#class Dochody(models.Model):
#	tytul     = models.CharField(max_length=30)
#	wartosc   = models.IntegerField()
#	data      =	models.DateField()
#	stalosc   = models.IntegerField()
#	kategoria = models.CharField(max_length=30)
#class Wydatki(models.Model):
#	tytul     = models.CharField(max_length=30)
#	wartosc   = models.IntegerField()
#	data      =	models.DateField()
#	stalosc   = models.IntegerField()

# Create your models here.

#class Employee(Document):
#    email = StringField(required=True)
#    first_name = StringField(max_length=50)
#    last_name = StringField(max_length=50)

class Dochody(Document):
	tytul     = StringField(max_length=30)
	wartosc   = IntField()
	data      = DateTimeField()
	stalosc   = IntField()
	kategoria = StringField(max_length=30)
class Wydatki(Document):
	tytul     = StringField(max_length=30)
	wartosc   = IntField()
	data      = DateTimeField()
	stalosc   = IntField()
