<?hh // strict

namespace Rime\ActionDispatch\Session\Csrf;

class CsrfToken
{
  
  protected $randval;
  protected $segment;
  
  public function __construct(\Rime\ActionDispatch\Session\Segment\Segment $segment, \Rime\ActionDispatch\Session\Implementation\RandvalInterface $randval)
  {
    $this->segment = $segment;
    $this->randval = $randval;
    if (! $this->segment->get('value')) 
    {
      $this->regenerateValue();
    }
  }
  
  public function isValid(?string $value): boolean
  {
    return $value === $this->getValue();
  }
  
  public function getValue(): ?string
  {
    return $this->segment->get('value');
  }
  
  public function regenerateValue(): void
  {
    $hash = hash('sha512', $this->randval->generate());
    $this->segment->set('value', $hash);
  }
}
