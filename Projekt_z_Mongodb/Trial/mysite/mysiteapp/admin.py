from django.contrib import admin

# Register your models here.

from django.contrib import admin
from komentarze.models import *

admin.site.register(Dochody)
admin.site.register(Wydatki)
