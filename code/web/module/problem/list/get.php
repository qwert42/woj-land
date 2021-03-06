<?php

require_once(MODULE_ROOT . '/problem/problem.func.php');

class Main extends cframe
{
    protected $need_login = false;

    public function process()
    {
        $volume = (int)request::$arr_get['volume'];
        $start  = land_conf::MIN_PROBLEM_ID 
                + ($volume - 1) * land_conf::PROBLEMS_PER_VOLUME;
        $end    = $start + land_conf::PROBLEMS_PER_VOLUME - 1;

        $sql = <<<eot
SELECT `problem_id`, `contest_id`, `title`, `submitted`, `accepted`
  FROM `problems`
  WHERE `problem_id` >= $start AND `problem_id` <=$end
eot;
        if (!is_admin())
        {
            $sql .= ' AND `enabled`=1';
        }
        $sql .= " ORDER BY `problem_id` ASC ";
        $conn = db_connect();
        fail_test($conn, false);
        $problems = db_fetch_lines($conn, $sql, land_conf::PROBLEMS_PER_VOLUME);
        db_close($conn);
        foreach ($problems as &$p)
        {
            $ac = $p['accepted'];
            $st = $p['submitted'];
            if ($st == 0)
            {
                $p['ratio'] = 0;
            }
            else
            {
                $p['ratio'] = round($ac * 100 / $st, 2);
            }
        }
        if (!is_admin())
            $problems = filter_contest_problem($problems);
        response::add_data('problems', $problems);
        response::add_data('volume', $volume);
        $solved_list = session::$is_login ? session::$user_info['solved_list'] : '';
        response::add_data('solved', $solved_list);

        return true;
    }

    public function display()
    {
        $this->set_my_tpl("list.tpl.php");
        return true;
    }
}

?>
