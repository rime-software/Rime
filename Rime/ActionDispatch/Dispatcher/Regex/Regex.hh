<?hh // strict

namespace Rime\ActionDispatch\Dispatcher\Regex;

class Regex
{
  
  protected $route;
  protected $regex;
  protected $matches;
  
  public function match(\Rime\ActionDispatch\Dispatcher\Route\Route $route, $path): int
  {
    $this->route = $route;
    $this->regex = $this->route->path;
    $this->setRegexOptionalParams();
    $this->setRegexParams();
    $this->setRegexWildcard();
    $this->regex = '#^' . $this->regex . '$#';
    return preg_match($this->regex, $path, $this->matches);
  }
  
  public function getMatches()
  {
    return $this->matches;
  }
  
  protected function setRegexOptionalParams(): void
  {
    preg_match('#{/([a-z][a-zA-Z0-9_,]*)}#', $this->regex, $matches);
    
    if ($matches) 
    {
      $repl = $this->getRegexOptionalParamsReplacement($matches[1]);
      $this->regex = str_replace($matches[0], $repl, $this->regex);
    }
  }
  
  protected function getRegexOptionalParamsReplacement(string $list): string
  {
    $list = explode(',', $list);
    $head = $this->getRegexOptionalParamsReplacementHead($list);
    $tail = '';
    
    foreach ($list as $name) 
    {
      $head .= "(/{{$name}}";
      $tail .= ')?';
    }
    
    return $head . $tail;
  }
  
  protected function getRegexOptionalParamsReplacementHead(&$list): string
  {
  
    // if the optional set is the first part of the path, make sure there
    // is a leading slash in the replacement before the optional param.
    $head = '';
    if (substr($this->regex, 0, 2) == '{/') 
    {
     $name = array_shift($list);
     $head = "/({{$name}})?";
    }
  
    return $head;
  }
  
  protected function setRegexParams(): void
  {
    $find = '#{([a-z][a-zA-Z0-9_]*)}#';
    preg_match_all($find, $this->regex, $matches, PREG_SET_ORDER);
  
    foreach ($matches as $match) 
    {
      $name = $match[1];
      $subpattern = $this->getSubpattern($name);
      $this->regex = str_replace("{{$name}}", $subpattern, $this->regex);
    
      if (! isset($this->route->values[$name])) 
      {
        $this->route->addValues(array($name => null));
      }
    }
  
  }
  
  protected function getSubpattern($name): string
  {
  
  // is there a custom subpattern for the name?
  if (isset($this->route->tokens[$name])) {
    return "(?P<{$name}>{$this->route->tokens[$name]})";
  }
  
    // use a default subpattern
    return "(?P<{$name}>[^/]+)";
  }
  
  protected function setRegexWildcard(): ?string
  {
  
    if (! $this->route->wildcard) 
    {
      return;
    }
    
    $this->regex = rtrim($this->regex, '/')
    . "(/(?P<{$this->route->wildcard}>.*))?";
  }
  
}