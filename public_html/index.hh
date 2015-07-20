<?hh // strict

  namespace Application
  {

    require_once '../Config/config.hh';

    $Rime = \Rime\System\Framework\Rime::getInstance();    
    $Rime->attach( new \Rime\System\Framework\Loader(),'load');
    $Rime->attach( new \Rime\ActionDispatch\Session\Factory\SessionFactory,'sessionFactory');
    $Rime->attach($viewMap,'viewMap');
    $Rime->attach($templateMap,'templateMap');

  //-------------------
  // Check Route Caching
    
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
      $Rime->attach($route,'route');
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
      
      $params = array();
      
      if( preg_match_all('/{+(.*?)}/', $route->path, $getParams) )
      {
        foreach($getParams[1] as $match)
        {
          $params[$match] = $route->params[$match];
        }
        unset($getParams);
      }
      
      if(method_exists($controller, $actionName))
      {
        $controller->filter($actionName);
        call_user_func_array(array($controller,$actionName), $params);
      }
      else
      {
        throw new \Rime\ActionController\Exception\UndefinedAction(
          "Call to undefined action '".$actionName."' in class ".get_class($controller)
        );
      }
  //-------------------
  // Make sure the controller can respond to the following formats
        
      if
      ( 
        ( method_exists($controller, 'canRespondTo') 
          && $controller->canRespondTo($route->params['format']) 
        )
        || 
        !$route->params['format'] 
      )
      {
        switch($route->params['format'])
        {
          
  //-------------------
  // JSON
          case '.json':
            header('Content-Type: application/json');
            echo json_encode($controller->getData(),JSON_PRETTY_PRINT);
            break;
            
  //-------------------
  // XML - Unsupported currently
  
          case '.xml':
            die('Unsupported');
            break;
            
  //-------------------
  // HTML
  
          case '.html':
          
            $controller->loadViewRegistries();
            $controller->view->addData((array)$controller->getData());

  //-------------------
  // Execute the requested action TODO: Add validation
            
            if(!$controller->view->getLayout())
            {
              $controller->view->setLayout(
                $route->params['template'] ? $route->params['template'] : 'master'
              );
            }
            
            if(is_bool($controller->getRenderer()->getData()->get('.html')))
            {
  
  //-------------------
  // HTML - rime.default
  
              $viewName = $controllerName.'/'.$actionName.'.hh';
              $controller->view->getViewRegistry()->set('rime.default',VIEW_PATH.'/'.$dir.$viewName);
              $controller->view->setView('rime.default');
                        
            }
            else
            {
              
  //-------------------
  // HTML - specified route
   
              $controller->view->setView(
                $controller->getRenderer()->getData()->get('.html')
              );
                
            }
            
            echo $controller->view->__invoke((array)$controller->getData());
            break;
            
  //-------------------
  // Custom return type, no type, or unknown specified  
          
          default:
            $actionName = str_replace('.', '', $route->params['format']);           
            if(method_exists('\Lib\Response\CustomResponse', $actionName))
              (new \Lib\Response\CustomResponse($controller))->$actionName();
            break;
        }
        
      }
      else
      {
  //-------------------
  // Internal Error - Controller is unable to respond to the requested format
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