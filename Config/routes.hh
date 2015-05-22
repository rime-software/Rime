<?hh // strict

use \Rime\ActionDispatch\Dispatcher as Dispatcher;

$router = (new Dispatcher\Factory\RouterFactory)->newInstance();

$router->addGet('home','/')->addValues(
	array(
		'controller'=>'index',
		'action'=>'index',
		'template'=>'master',
		'format'=>'html'
	)
);

$router->attach('index','/index', function ($router) {
  $router->add('index', '{format}')
    ->addTokens(array(
      'format' => '(\.json|\.xml|\.html)?'
    ))
    ->addValues(array(
      'format' => '.html',
      'controller' => 'index',
      'action' => 'index'
    ));
});