<?hh // strict

namespace Rime\ActionDispatch;

class AbstractSpec
{
  protected array $tokens      = array();
  protected array $server      = array();
  protected array $method      = array();
  protected array $accept      = array();
  protected array $values      = array();
  protected $secure      = null;
  protected $wildcard    = null;
  protected $routable    = true;
  protected $is_match    = null;
  protected $generate    = null;  
    

  public function setTokens(array $tokens): AbstractSpec
  {
    $this->tokens = $tokens;
    return $this;
  }
  
  public function addTokens(array $tokens): AbstractSpec
  {
    $this->tokens = array_merge($this->tokens, $tokens);
    return $this;
  }
  
  public function setServer(array $server): AbstractSpec
  {
    $this->server = $server;
    return $this;
  }
  
  public function addServer(array $server): AbstractSpec
  {
    $this->server = array_merge($this->server, $server);
    return $this;
  }
  
  public function setMethod($method): AbstractSpec
  {
    $this->method = (array) $method;
    return $this;
  }
  
  public function addMethod($method): AbstractSpec
  {
    $this->method = array_merge($this->method, (array) $method);
    return $this;
  }
  
  public function setAccept($accept): AbstractSpec
  {
    $this->accept = (array) $accept;
    return $this;
  }
  
  public function addAccept($accept): AbstractSpec
  {
    $this->accept = array_merge($this->accept, (array) $accept);
    return $this;
  }
  
  public function setValues(array $values): AbstractSpec
  {
    $this->values = $values;
    return $this;
  }
  
  public function addValues(array $values): AbstractSpec
  {
    $this->values = array_merge($this->values, $values);
    return $this;
  }
  
  public function setSecure($secure = true): AbstractSpec
  {
    $this->secure = ($secure === null) ? null : (bool) $secure;
    return $this;
  }
  
  public function setWildcard(?string $wildcard): AbstractSpec
  {
    $this->wildcard = $wildcard;
    return $this;
  }
  
  public function setRoutable($routable = true): AbstractSpec
  {
    $this->routable = (bool) $routable;
    return $this;
  }
  
  public function setIsMatchCallable($is_match): AbstractSpec
  {
    $this->is_match = $is_match;
    return $this;
  }
  
  public function setGenerateCallable($generate): AbstractSpec
  {
    $this->generate = $generate;
    return $this;
  }
    
}