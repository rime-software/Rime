<?hh // strict

require_once 'exception/Exception.hh';
require_once 'exception/RouteNotFound.hh';
require_once 'exception/UnexpectedValue.hh';
require_once 'spec/AbstractSpec.hh';
require_once 'route/RouteGenerator.hh';
require_once 'regex/Regex.hh';
require_once 'route/Route.hh';
require_once 'route/RouteCollection.hh';
require_once 'factories/RouteFactory.hh';
require_once 'route/Router.hh';
require_once 'factories/RouterFactory.hh';

$router_factory = new \Rime\ActionDispatch\RouterFactory;
$router = $router_factory->newInstance();