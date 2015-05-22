<?hh // strict
    
  namespace Application
  {
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
        $controller = new BASE_PATH.$controllerName();
      }
      
  //-------------------
  // Load in the registries
      $controller->view->setRegistries(
        new \Rime\ActionView\Registry\TemplateRegistry($viewMap),
        new \Rime\ActionView\Registry\TemplateRegistry($templateMap)
      );
  //-------------------
  // Execute the requested action TODO: Add validation
  
      $controller->$actionName();
      echo "<pre>";

  //-------------------
  // Make sure the controller can respond to the following formats
      if( $controller->canRespondTo($route->params['format']) )
      {
        
      }
      else
      {
        die('Unable to respond to: '.$route->params['format']);
      }
    }
    else
    {
      
  //-------------------
  // 404 - Page Not Found
      die('not found');
         
    }   
  }