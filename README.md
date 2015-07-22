# Rime
Rime MVC Framework

## Getting Started - Heroku
Heroku is a great (and free) way to familiarize yourself with the Rime framework without having to compile the HHVM and XHP extensions yourself.

1. Install Heroku and Git if you have not already.
2. Clone the Rime repository.
<pre>
$ git clone https://github.com/rime-software/Rime.git
</pre>
3. Navigate to the Rime repository
<pre>
$ cd Rime
</pre>
4. Set up the Procfile so Heroku knows how to run Rime (We'll use apache in this case)
<pre>
$ echo 'web: vendor/bin/heroku-hhvm-apache2 public_html/' > Procfile
</pre>
5. Configure the .htaccess rules for clean URLs
<pre>
Options +FollowSymLinks
RewriteEngine On
RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_URI} !\.(css|js|jpg|png)$
RewriteRule ^(.*)$ index.php?/$1 [L,P,QSA]
</pre>
6. Configure your Composer to install the HHVM on Heroku (XHP is not show in this case)
<pre>
{
  "name": "Rime Framework",
  "require": {
     "hhvm": "~3.5"
  }
}
</pre>
7. Push to heroku
<pre>
$ heroku create
...
$ git push heroku master
...
$ heroku open
</pre>

### Your Done!
You should see the following message on your site:
<pre>
See me in Application/Views/index/index.hh!
</pre>
