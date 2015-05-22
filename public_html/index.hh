<?hh // strict
    
  namespace Application
  {
    
  /*************************************************************************/
  /* ActionView Alias: \Rime\ActionView\{directory}\ClassName              */
  /*************************************************************************/  
    use \Rime\ActionView      as ActionView;
    use \Rime\ActionView\View as Template;
    
  /**********************************************************************************/
  /* ActionDispatch Alias: \Rime\ActionDispatch\{package}\{directory}\ClassName     */
  /**********************************************************************************/
  
    use \Rime\ActionDispatch\Dispatcher as Dispatcher;
    use \Rime\ActionDispatch\Session    as Session;

  /**********************************************************************************/
  /* Require Any Additional Files      */
  /**********************************************************************************/  
    require_once '../Config/config.hh';

  	if(!DEV_MODE)
  	{
  		$routeCache = CACHE_PATH.'/routes.cache';
  
  		if(file_exists($routeCache))
  		{
  			$routes = unserialize(file_get_contents($routeCache));
  			$router->setRoutes($routes);			
  		}
  		else
  		{
  			require_once CONFIG_PATH.'/routes.hh';
  			$routes = $router->getRoutes();
  			file_put_contents($routeCache, serialize($routes));			
  		}
  	}
  	
  //-------------------
  // Parse the request URI, add a trailing slash if non-existant
    	
  	$_SERVER['REQUEST_URI'] = (substr($_SERVER['REQUEST_URI'],-1) == '/' && strlen($_SERVER['REQUEST_URI']) > 1) ? substr($_SERVER['REQUEST_URI'],0,-1) : $_SERVER['REQUEST_URI'];
  	$path = parse_url($_SERVER["REQUEST_URI"], PHP_URL_PATH);
  	$route = $router->match($path, $_SERVER);
  
  //-------------------
  // Check whether a route has been found
  
    if ($route)
    {
  		$controllerName = $route->params['controller'];
  		$actionName = $route->params['action'];
  		$dir = isset($route->params['directory']) && $route->params['directory'] ? str_replace('/','\\',$route->params['directory'].'/') : '';
  		
  //-------------------
  // If the controller name does not have a namespace
  // load from the default Application namespace
  		if( substr($controllerName,-1) != '\\' )
      {
        $controllerFile = '\\Application\\Controllers\\'.$dir.$controllerName.'Controller';
        $controller = new $controllerFile();
        unset($controllerFile);
      }
      else
      {
        $controller = new $controllerName();
      }
      $controller->$actionName();
    }
    else
    {
  //-------------------
  // 404 - Page Not Found
         
    }   
  }