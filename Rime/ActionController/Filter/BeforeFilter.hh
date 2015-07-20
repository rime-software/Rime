<?hh // strict

namespace Rime\ActionController\Filter;

class BeforeFilter implements \Rime\ActionController\Filter\iFilter
{
  private ?string $action;
  private array   $filter_actions = array();
  private ?string $filter_method;
  
  public function filter(string $action, array $filters): array
  {
    $this->action = $action;
    
    foreach($filters as $filter_method => $included_actions)
    {
      $this->filter_method = $filter_method;
      
      $this->filter_action_list('except', $included_actions, false);
      $this->filter_action_list('only', $included_actions, true);
    }
    
    return $this->filter_actions;
  }
  
  private function filter_action_list(string $filter_type, array $action_list, bool $add): void
  {
    if(array_key_exists($filter_type, $action_list))
    {
      if( in_array($this->action, $action_list[$filter_type]) == $add )
      {
        $this->filter_actions[] = $this->filter_method;
      }
    }
  }
  
}