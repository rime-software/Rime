<?hh // strict

namespace Rime\ActionDispatch\Session\User;

class Session
{
  
  const string FLASH_NEXT = 'Rime\ActionDispatch\Session\Flash\Next';
  const string FLASH_NOW = 'Rime\ActionDispatch\Session\Flash\Now';
  
  protected SegmentFactory $segment_factory;
  protected CsrfToken $csrf_token;
  protected CsrfTokenFactory $csrf_token_factory;
  protected array $cookies;
  protected array $cookie_params = array();
  protected Phpfunc $phpfunc;
  protected $delete_cookie;
  protected boolean $flash_moved = false;
  
  public function __construct(
    \Rime\ActionDispatch\Session\Factory\SegmentFactory $segment_factory,
    \Rime\ActionDispatch\Session\Factory\CsrfTokenFactory $csrf_token_factory,
    \Rime\ActionDispatch\Session\User\Phpfunc $phpfunc,
    array $cookies = array(),
    $delete_cookie = null
  ) {
    $this->segment_factory    = $segment_factory;
    $this->csrf_token_factory = $csrf_token_factory;
    $this->phpfunc            = $phpfunc;
    $this->cookies            = $cookies;
  
    $this->setDeleteCookie($delete_cookie);
  
    $this->cookie_params = $this->phpfunc->session_get_cookie_params();
  }
  
  public function setDeleteCookie($delete_cookie): void
  {
    $this->delete_cookie = $delete_cookie;
    if (! $this->delete_cookie) 
    {
      $phpfunc = $this->phpfunc;
      $this->delete_cookie = function (
        $name,
        $params
      ) use ($phpfunc) {
        $phpfunc->setcookie(
          $name,
          '',
          time() - 42000,
          $params['path'],
          $params['domain']
        );
      };
    }
  }
  
  public function getSegment(string $name): \Rime\ActionDispatch\Session\Segment\Segment
  {
    return $this->segment_factory->newInstance($this, $name);
  }
  
  public function isResumable(): boolean
  {
    $name = $this->getName();
    return isset($this->cookies[$name]);
  }
  
  public function isStarted(): boolean
  {
    if ($this->phpfunc->function_exists('session_status')) 
    {
      $started = $this->phpfunc->session_status() === PHP_SESSION_ACTIVE;
    } 
    else 
    {
      $started = $this->sessionStatus();
    }
  
    // if the session was started externally, move the flash values forward
    if ($started && ! $this->flash_moved) 
    {
      $this->moveFlash();
    }

    // done
    return $started;
  }
  
  protected function sessionStatus(): mixed
  {
    $setting = 'session.use_trans_sid';
    $current = $this->phpfunc->ini_get($setting);
    $level   = $this->phpfunc->error_reporting(0);
    $result  = $this->phpfunc->ini_set($setting, $current);
    $this->phpfunc->error_reporting($level);
    return $result !== $current;
  }
  
  public function start(): boolean
  {
    $result = $this->phpfunc->session_start();
    if ($result) 
    {
      $this->moveFlash();
    }
    return $result;
  }
  
  protected function moveFlash(): void
  {
    if (! isset($_SESSION[Session::FLASH_NEXT])) 
    {
      $_SESSION[Session::FLASH_NEXT] = array();
    }
    $_SESSION[Session::FLASH_NOW] = $_SESSION[Session::FLASH_NEXT];
    $_SESSION[Session::FLASH_NEXT] = array();
    $this->flash_moved = true;
  }
  
  public function resume(): boolean
  {
    if ($this->isStarted()) 
    {
      return true;
    }
  
    if ($this->isResumable()) 
    {
      return $this->start();
    }
    
    return false;
  }
  
  public function clear(): mixed
  {
    return $this->phpfunc->session_unset();
  }
  
  public function commit(): mixed
  {
    return $this->phpfunc->session_write_close();
  }
  
  public function destroy(): boolean
  {
    if (! $this->isStarted()) 
    {
      $this->start();
    }
  
    $name = $this->getName();
    $params = $this->getCookieParams();
    $this->clear();
  
    $destroyed = $this->phpfunc->session_destroy();
    if ($destroyed) 
    {
      call_user_func($this->delete_cookie, $name, $params);
    }
  
    return $destroyed;
  }
  
  public function getCsrfToken(): \Rime\ActionDispatch\Session\Csrf\CsrfToken
  {
    if (! $this->csrf_token) 
    {
      $this->csrf_token = $this->csrf_token_factory->newInstance($this);
    }
  
    return $this->csrf_token;
  }
  
  public function setCacheExpire($expire): int
  {
    return $this->phpfunc->session_cache_expire($expire);
  }
  
  public function getCacheExpire(): int
  {
    return $this->phpfunc->session_cache_expire();
  }
  
  public function setCacheLimiter(?string $limiter): string
  {
    return $this->phpfunc->session_cache_limiter($limiter);
  }
  
  public function getCacheLimiter(): string
  {
    return $this->phpfunc->session_cache_limiter();
  }
  
  public function setCookieParams(array $params): void
  {
    $this->cookie_params = array_merge($this->cookie_params, $params);
    $this->phpfunc->session_set_cookie_params(
      $this->cookie_params['lifetime'],
      $this->cookie_params['path'],
      $this->cookie_params['domain'],
      $this->cookie_params['secure'],
      $this->cookie_params['httponly']
    );
  }
  
  public function getCookieParams(): array
  {
    return $this->cookie_params;
  }
  
  public function getId(): string
  {
    return $this->phpfunc->session_id();
  }
  
  public function regenerateId(): boolean
  {
    $result = $this->phpfunc->session_regenerate_id(true);
    if ($result && $this->csrf_token) 
    {
      $this->csrf_token->regenerateValue();
    }
    return $result;
  }
  
  public function setName(?string $name): string
  {
    return $this->phpfunc->session_name($name);
  }
  
  public function getName(): string
  {
    return $this->phpfunc->session_name();
  }
  
  public function setSavePath($path): string
  {
    return $this->phpfunc->session_save_path($path);
  }
  
  public function getSavePath(): string
  {
    return $this->phpfunc->session_save_path();
  }
}
